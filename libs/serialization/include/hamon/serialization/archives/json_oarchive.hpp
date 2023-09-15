/**
 *	@file	json_oarchive.hpp
 *
 *	@brief	json_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_ARCHIVES_JSON_OARCHIVE_HPP
#define HAMON_SERIALIZATION_ARCHIVES_JSON_OARCHIVE_HPP

#include <hamon/serialization/detail/archive_base.hpp>
#include <hamon/serialization/detail/text_oarchive_impl.hpp>
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

class json_oarchive : public detail::archive_base
{
public:
	template <typename OStream>
	explicit json_oarchive(OStream& os)
		: m_impl(new detail::text_oarchive_impl<OStream>(os))
	{
		start_object();
	}
	
	~json_oarchive()
	{
		end_object();
	}

	template <typename T>
	json_oarchive& operator<<(nvp<T> const& t)
	{
		if (!m_first_value)
		{
			m_impl->put(",\n");
		}
		m_first_value = false;

		m_impl->put(get_indent_string());
		hamon::serialization::detail::save_value(*this, t.name());
		m_impl->put(": ");
		hamon::serialization::detail::save_value(*this, t.value());
		return *this;
	}

	template <typename T>
	json_oarchive& operator<<(T const& t)
	{
		auto const name =
			hamon::string("value") + std::to_string(get_value_index());
		increment_value_index();
		return *this << make_nvp(name, t);
	}

	template <typename T>
	json_oarchive& operator&(T const& t)
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

	void start_object(void)
	{
		m_impl->put("{\n");
		increment_indent_level();
		m_first_value = true;
	}

	void end_object(void)
	{
		m_impl->put("\n");
		decrement_indent_level();
		m_impl->put(get_indent_string());
		m_impl->put("}");
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
			case '"':  result.append({'\\', '"'});  break;
			case '\\': result.append({'\\', '\\'}); break;
			case '/':  result.append({'\\', '/'});  break;
			case '\b': result.append({'\\', 'b'});  break;
			case '\f': result.append({'\\', 'f'});  break;
			case '\n': result.append({'\\', 'n'});  break;
			case '\r': result.append({'\\', 'r'});  break;
			case '\t': result.append({'\\', 't'});  break;
			default:   result.append(1, c); break;
			}
		}
		return result;
	}

	template <typename CharT>
	static hamon::basic_string<CharT> quote(hamon::basic_string<CharT> const& str)
	{
		return
			hamon::basic_string<CharT>(1, CharT('"')) +
			str +
			hamon::basic_string<CharT>(1, CharT('"'));
	}

private:
	template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		// TODO: inf, nan のときはダブルコーテーションでクォートする
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

	friend void save_arithmetic(json_oarchive& oa, bool const& t)
	{
		oa.m_impl->save(t);
	}

	template <typename T>
	friend void save_arithmetic(json_oarchive& oa, T const& t)
	{
		oa.save_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void save_string(json_oarchive& oa, T const& t)
	{
		oa.m_impl->save_string(quote(escape(t)));
	}

	template <typename T>
	friend void save_array(json_oarchive& oa, T const& t)
	{
		oa.m_impl->put("[\n");
		oa.increment_indent_level();
		hamon::size_t i = 0;
		for (auto const& x : t)
		{
			if (i != 0)
			{
				oa.m_impl->put(",\n");
			}
			oa.m_impl->put(oa.get_indent_string());
			hamon::serialization::detail::save_value(oa, x);
			++i;
		}
		oa.m_impl->put("\n");
		oa.decrement_indent_level();
		oa.m_impl->put(oa.get_indent_string());
		oa.m_impl->put("]");
	}

	template <typename T>
	friend void save_vector(json_oarchive& oa, T const& t)
	{
		save_array(oa, t);
	}

	friend void start_save_class(json_oarchive& oa)
	{
		oa.start_object();
	}

	friend void end_save_class(json_oarchive& oa)
	{
		oa.end_object();
	}

private:
	std::unique_ptr<detail::text_oarchive_impl_base>	m_impl;
	hamon::string		m_indent_string_element = "    ";
	std::stack<int>		m_value_index_stack;
	bool				m_first_value = true;
};

}	// namespace serialization

}	// namespace hamon

#include <hamon/serialization/register_archive.hpp>
HAMON_SERIALIZATION_REGISTER_OARCHIVE(hamon::serialization::json_oarchive)

#endif // HAMON_SERIALIZATION_ARCHIVES_JSON_OARCHIVE_HPP
