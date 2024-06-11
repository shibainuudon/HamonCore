/**
 *	@file	quoted_impl.hpp
 *
 *	@brief
 */

#ifndef HAMON_IOMANIP_DETAIL_QUOTED_IMPL_HPP
#define HAMON_IOMANIP_DETAIL_QUOTED_IMPL_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/ios/flags_saver.hpp>
#include <hamon/string.hpp>
#include <ostream>	// basic_ostream
#include <istream>	// basic_istream
#include <ios>		// noskipws

namespace hamon
{

namespace detail
{

template <typename Traits1, typename Traits2, typename = void>
struct is_compatible_char_traits
	: public hamon::false_type {};

template <typename Traits1, typename Traits2>
struct is_compatible_char_traits<Traits1, Traits2,
	hamon::enable_if_t<
		hamon::is_same<
			typename Traits1::char_type,
			typename Traits2::char_type
		>::value
	>
> : public hamon::true_type {};

template <typename CharT, typename Traits>
struct quoted_output
{
public:
	template <typename Size>
	explicit quoted_output(CharT const* s, Size len, CharT delim, CharT escape)
		: m_first(s), m_last(s + len), m_delim(delim), m_escape(escape)
	{}

private:
	CharT const*	m_first;
	CharT const*	m_last;
	CharT			m_delim;
	CharT			m_escape;

private:
	template <typename Traits2,
		typename = hamon::enable_if_t<
			hamon::is_same<Traits, void>::value ||
			hamon::detail::is_compatible_char_traits<Traits, Traits2>::value
		>>
	friend std::basic_ostream<CharT, Traits2>&
	operator<<(std::basic_ostream<CharT, Traits2>& os, quoted_output const& q)
	{
		auto first = q.m_first;
		auto const last = q.m_last;
		auto const delim = q.m_delim;
		auto const escape = q.m_escape;

		hamon::basic_string<CharT, Traits2> str;

		// [quoted.manip]/2.1
		str.push_back(delim);

		// [quoted.manip]/2.2
		for (; first != last; ++first)
		{
			if (Traits2::eq(*first, escape) || Traits2::eq(*first, delim))
			{
				str.push_back(escape);
			}
			str.push_back(*first);
		}

		// [quoted.manip]/2.3
		str.push_back(delim);

		return os << str;
	}
};

template <typename String>
struct quoted_input
{
private:
	using CharT = typename String::value_type;
	using Traits = typename String::traits_type;

public:
	explicit quoted_input(String& str, CharT delim, CharT escape)
		: m_str(str), m_delim(delim), m_escape(escape)
	{}

private:
	String& m_str;
	CharT	m_delim;
	CharT	m_escape;

private:
	template <typename Traits2,
		typename = hamon::enable_if_t<
			hamon::detail::is_compatible_char_traits<Traits, Traits2>::value
		>>
	friend std::basic_ostream<CharT, Traits2>&
	operator<<(std::basic_ostream<CharT, Traits2>& os, quoted_input const& q)
	{
		// [quoted.manip]/3.2
		return os << quoted_output<CharT, Traits>{q.m_str.data(), q.m_str.size(), q.m_delim, q.m_escape};
	}

	template <typename Traits2,
		typename = hamon::enable_if_t<
			hamon::detail::is_compatible_char_traits<Traits, Traits2>::value
		>>
	friend std::basic_istream<CharT, Traits2>&
	operator>>(std::basic_istream<CharT, Traits2>& is, quoted_input const& q)
	{
		auto& s = q.m_str;
		auto const delim = q.m_delim;
		auto const escape = q.m_escape;

		CharT c;
		is >> c;
		if (is.fail())
		{
			return is;
		}

		// [quoted.manip]/3.1.1
		if (!Traits2::eq(c, delim))
		{
			is.unget();
			// [quoted.manip]/3.1.2
			return is >> s;
		}

		// [quoted.manip]/3.1.1.5
		hamon::ios::flags_saver fs(is);

		// [quoted.manip]/3.1.1.1
		std::noskipws(is);

		// [quoted.manip]/3.1.1.2
		s.clear();

		// [quoted.manip]/3.1.1.3
		while (true)
		{
			is >> c;
			if (is.fail())
			{
				break;
			}

			if (Traits2::eq(c, escape))
			{
				is >> c;
				if (is.fail())
				{
					break;
				}
			}
			else if (Traits2::eq(c, delim))
			{
				// [quoted.manip]/3.1.1.4
				break;
			}

			s.push_back(c);
		}

		return is;
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_IOMANIP_DETAIL_QUOTED_IMPL_HPP
