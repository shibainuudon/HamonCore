/**
 *	@file	json_iarchive.hpp
 *
 *	@brief	json_iarchiveの定義
 */

#ifndef HAMON_SERIALIZATION_JSON_IARCHIVE_HPP
#define HAMON_SERIALIZATION_JSON_IARCHIVE_HPP

#include <hamon/serialization/detail/text_iarchive_impl.hpp>
#include <hamon/serialization/detail/load_value.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <type_traits>
#include <cstdint>
#include <memory>

namespace hamon
{

namespace serialization
{

class json_iarchive
{
public:
	template <typename IStream>
	explicit json_iarchive(IStream& is)
		: m_impl(new detail::text_iarchive_impl<IStream>(is))
	{
		start_object();
	}

	~json_iarchive()
	{
		end_object();
	}

	template <typename T>
	json_iarchive& operator>>(nvp<T> const& t)
	{
		if (!m_first_value)
		{
			m_impl->get_one_char();	// ","
		}
		m_first_value = false;

		std::string name;
		hamon::serialization::detail::load_value(*this, name);
		m_impl->get_one_char();		// ":"
		hamon::serialization::detail::load_value(*this, t.value());
		return *this;
	}

	template <typename T>
	json_iarchive& operator>>(T& t)
	{
		return *this >> make_nvp("", t);
	}

	template <typename T>
	json_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	void start_object(void)
	{
		m_impl->get_one_char();	// "{"
		m_first_value = true;
	}

	void end_object(void)
	{
		m_impl->get_one_char();	// "}"
	}

	template <typename CharT>
	static std::basic_string<CharT> unescape(std::basic_string<CharT> const& str)
	{
		bool escaping = false;
		std::basic_string<CharT> result;
		for (auto c : str)
		{
			if (escaping)
			{
				switch (c)
				{
				case '"':  c = '"';  break;
				case '\\': c = '\\'; break;
				case '/':  c = '/';  break;
				case 'b':  c = '\b'; break;
				case 'f':  c = '\f'; break;
				case 'n':  c = '\n'; break;
				case 'r':  c = '\r'; break;
				case 't':  c = '\t'; break;
				}
				escaping = false;
			}
			else
			{
				if (c == '\\')
				{
					escaping = true;
					continue;
				}
			}

			result += c;
		}
		return result;
	}

private:
	template <typename T, typename = hamon::enable_if_t<std::is_floating_point<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<2>)
	{
		m_impl->load(t);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_unsigned<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<1>)
	{
		std::uintmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}
	template <typename T, typename = hamon::enable_if_t<std::is_signed<T>::value>>
	void load_arithmetic_impl(T& t, hamon::detail::overload_priority<0>)
	{
		std::intmax_t i;
		m_impl->load(i);
		t = static_cast<T>(i);
	}

	friend void load_arithmetic(json_iarchive& ia, bool& t)
	{
		ia.m_impl->load(t);
	}

	template <typename T>
	friend void load_arithmetic(json_iarchive& ia, T& t)
	{
		ia.load_arithmetic_impl(t, hamon::detail::overload_priority<2>{});
	}

	template <typename T>
	friend void load_string(json_iarchive& ia, T& t)
	{
		T tmp;
		ia.m_impl->load_quoted_string(tmp);
		t = unescape(tmp);
	}

	template <typename T>
	friend void load_array(json_iarchive& ia, T& t)
	{
		ia.m_impl->get_one_char();	// "["
		for (std::size_t i = 0; i < std::extent<T>::value; ++i)
		{
			if (i != 0)
			{
				ia.m_impl->get_one_char();	// ","
			}
			hamon::serialization::detail::load_value(ia, t[i]);
		}
		ia.m_impl->get_one_char();	// "]"
	}

	friend void start_load_class(json_iarchive& ia)
	{
		ia.start_object();
	}

	friend void end_load_class(json_iarchive& ia)
	{
		ia.end_object();
	}

private:
	std::unique_ptr<detail::text_iarchive_impl_base>	m_impl;
	bool	m_first_value = true;
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_JSON_IARCHIVE_HPP
