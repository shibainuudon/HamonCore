/**
 *	@file	json_oarchive.hpp
 *
 *	@brief	json_oarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_JSON_OARCHIVE_HPP
#define HAMON_SERIALIZATION_JSON_OARCHIVE_HPP

#include <hamon/serialization/detail/text_oarchive_impl.hpp>
#include <hamon/serialization/detail/save_value.hpp>
#include <hamon/serialization/nvp.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <type_traits>
#include <cstdint>
#include <memory>
#include <stack>

namespace hamon
{

namespace serialization
{

class json_oarchive
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
			std::string("value") + std::to_string(get_value_index());
		increment_value_index();
		return *this << make_nvp(name, t);
	}

	template <typename T>
	json_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	void push(void)
	{
		m_value_index_stack.push(0);
	}

	void pop(void)
	{
		m_value_index_stack.pop();
	}

	void start_object(void)
	{
		m_impl->put("{\n");
		push();
		m_first_value = true;
	}

	void end_object(void)
	{
		m_impl->put("\n");
		pop();
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

	std::size_t get_indent_level(void) const
	{
		return m_value_index_stack.size();
	}

	std::string get_indent_string(void) const
	{
		std::string s;
		for (std::size_t i = 0; i < get_indent_level(); ++i)
		{
			s += m_indent_string_element;
		}
		return s;
	}

	template <typename CharT>
	static std::basic_string<CharT> escape(std::basic_string<CharT> const& str)
	{
		std::basic_string<CharT> result;
		for (auto const& c : str)
		{
			switch (c)
			{
			case '"':  result += c; break;
			case '\\': result += '\\'; result += '\\'; break;
			case '/':  result += '\\'; result += '/';  break;
			case '\b': result += '\\'; result += 'b';  break;
			case '\f': result += '\\'; result += 'f';  break;
			case '\n': result += '\\'; result += 'n';  break;
			case '\r': result += '\\'; result += 'r';  break;
			case '\t': result += '\\'; result += 't';  break;
			default:   result += c; break;
			}
		}
		return result;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<2>)
	{
		m_impl->save(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<1>)
	{
		m_impl->save(static_cast<std::uintmax_t>(t));
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void save_arithmetic_impl(T const& t, hamon::detail::overload_priority<0>)
	{
		m_impl->save(static_cast<std::intmax_t>(t));
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
		auto escaped_str = escape(t);
		oa.m_impl->save_quoted_string(escaped_str);
	}

	template <typename T>
	friend void save_array(json_oarchive& oa, T const& t)
	{
		oa.m_impl->put("[\n");
		oa.push();
		for (std::size_t i = 0; i < std::extent<T>::value; ++i)
		{
			if (i != 0)
			{
				oa.m_impl->put(",\n");
			}
			oa.m_impl->put(oa.get_indent_string());
			hamon::serialization::detail::save_value(oa, t[i]);
		}
		oa.m_impl->put("\n");
		oa.pop();
		oa.m_impl->put(oa.get_indent_string());
		oa.m_impl->put("]");
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
	std::string			m_indent_string_element = "    ";
	std::stack<int>		m_value_index_stack;
	bool				m_first_value = true;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_JSON_OARCHIVE_HPP
