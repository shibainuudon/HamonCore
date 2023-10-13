/**
 *	@file	xml_oarchive.hpp
 *
 *	@brief	xml_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_ARCHIVES_XML_OARCHIVE_HPP
#define HAMON_SERIALIZATION_ARCHIVES_XML_OARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/xml_oarchive_impl.hpp>
#include <hamon/serialization/detail/save_value.hpp>
#include <hamon/serialization/types/string.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/cstdint/uintmax_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/string.hpp>
#include <memory>
#include <stack>

namespace hamon
{

namespace serialization
{

class xml_oarchive : public detail::archive_base
{
public:
	template <typename OStream>
	explicit xml_oarchive(OStream& os)
		: m_impl(new detail::xml_oarchive_impl<OStream>(os))
	{
		m_impl->put("<?xml version=\"1.0\"?>");
		start_tag("serialization");
		start_object();
	}
	
	~xml_oarchive()
	{
		end_object();
		end_tag();
	}

	template <typename T>
	xml_oarchive& operator<<(nvp<T> const& t)
	{
		start_tag(t.name());
		hamon::serialization::detail::save_value(*this, t.value());
		end_tag();
		return *this;
	}

	template <typename T>
	xml_oarchive& operator<<(T const& t)
	{
		auto const name =
			hamon::string("value") + hamon::to_string(get_value_index());
		increment_value_index();
		return *this << make_nvp(name, t);
	}

	template <typename T>
	xml_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	void increment_indent_level(void)
	{
		m_value_index_stack.push(0);
	}

	void decrement_indent_level(void)
	{
		m_value_index_stack.pop();
	}

	void start_tag(hamon::string const& tag_name)
	{
		m_tag_name_stack.push(tag_name);
		m_impl->put("\n");
		m_impl->put(get_indent_string());
		m_impl->put(quote_start_tag(tag_name));
	}

	void end_tag(void)
	{
		m_impl->put(quote_end_tag(m_tag_name_stack.top()));
		m_tag_name_stack.pop();
	}
	
	void start_object(void)
	{
		increment_indent_level();
	}

	void end_object(void)
	{
		decrement_indent_level();
		m_impl->put("\n");
		m_impl->put(get_indent_string());
	}

	int get_value_index(void) const
	{
		return m_value_index_stack.top();
	}

	void increment_value_index(void)
	{
		m_value_index_stack.top()++;
	}

	hamon::size_t get_indent_level(void) const
	{
		return m_value_index_stack.size();
	}

	hamon::string get_indent_string(void) const
	{
		hamon::string s;
		for (hamon::size_t i = 0; i < get_indent_level(); ++i)
		{
			s += m_indent_string_element;
		}
		return s;
	}

	template <typename CharT>
	static hamon::basic_string<CharT> escape(hamon::basic_string<CharT> const& str)
	{
		hamon::basic_string<CharT> result;
		for (auto const& c : str)
		{
			switch (c)
			{
			case '"':  result.append({'&', 'q', 'u', 'o', 't', ';'}); break;
			case '\'': result.append({'&', 'a', 'p', 'o', 's', ';'}); break;
			case '<':  result.append({'&', 'l', 't', ';'}); break;
			case '>':  result.append({'&', 'g', 't', ';'}); break;
			case '&':  result.append({'&', 'a', 'm', 'p', ';'}); break;
			default:   result.append(1, c); break;
			}
		}
		return result;
	}

	template <typename CharT>
	static hamon::basic_string<CharT> quote_start_tag(hamon::basic_string<CharT> const& str)
	{
		return
			hamon::basic_string<CharT>(1, CharT('<')) +
			str +
			hamon::basic_string<CharT>(1, CharT('>'));
	}

	template <typename CharT>
	static hamon::basic_string<CharT> quote_end_tag(hamon::basic_string<CharT> const& str)
	{
		return
			hamon::basic_string<CharT>(1, CharT('<')) +
			hamon::basic_string<CharT>(1, CharT('/')) +
			str +
			hamon::basic_string<CharT>(1, CharT('>'));
	}

private:
	template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		m_impl->save(t);
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<1>)
	{
		m_impl->save(static_cast<hamon::uintmax_t>(t));
	}
	template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<0>)
	{
		m_impl->save(static_cast<hamon::intmax_t>(t));
	}

	friend void save_arithmetic(xml_oarchive& oa, bool const& t)
	{
		oa.m_impl->save(t);
	}

	template <typename T>
	friend void save_arithmetic(xml_oarchive& oa, T const& t)
	{
		oa.save_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void save_string(xml_oarchive& oa, T const& t)
	{
		oa.m_impl->save_string(escape(t));
	}

	template <typename T>
	friend void save_array(xml_oarchive& oa, T const& t)
	{
		oa.start_object();
		for (auto const& x : t)
		{
			oa << x;
		}
		oa.end_object();
	}
	
	template <typename T>
	friend void save_vector(xml_oarchive& oa, T const& t)
	{
		save_array(oa, t);
	}

	friend void start_save_class(xml_oarchive& oa)
	{
		oa.start_object();
	}

	friend void end_save_class(xml_oarchive& oa)
	{
		oa.end_object();
	}

private:
	std::unique_ptr<detail::xml_oarchive_impl_base>	m_impl;
	hamon::string			  m_indent_string_element = "    ";
	std::stack<int>		      m_value_index_stack;
	std::stack<hamon::string> m_tag_name_stack;
};

}	// namespace serialization

}	// namespace hamon

#include <hamon/serialization/register_archive.hpp>
HAMON_SERIALIZATION_REGISTER_OARCHIVE(hamon::serialization::xml_oarchive)

#endif // HAMON_SERIALIZATION_ARCHIVES_XML_OARCHIVE_HPP
