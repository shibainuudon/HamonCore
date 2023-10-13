/**
 *	@file	getline.hpp
 *
 *	@brief	getline の定義
 */

#ifndef HAMON_STRING_GETLINE_HPP
#define HAMON_STRING_GETLINE_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::getline;

}	// namespace hamon

#else

#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>
#include <ios>		// ios_base, streamsize
#include <istream>	// basic_istream

namespace hamon
{

// 23.4.4.4 [string.io],Inserters and extractors

template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_istream<CharT, Traits>&
getline(
	std::basic_istream<CharT, Traits>& is,
	basic_string<CharT, Traits2, Allocator>& str, CharT delim)
{
	// 31.7.5.4 [istream.unformatted], Unformatted input functions
	std::ios_base::iostate state = std::ios_base::goodbit;
	typename std::basic_istream<CharT, Traits>::sentry sen(is, true);
	if (sen)
	{
#if !defined(HAMON_NO_EXCEPTIONS)
		try
		{
#endif
			// [string.io]/6
			str.erase();
			std::streamsize extracted = 0;
			while (true)
			{
				typename Traits::int_type const i = is.rdbuf()->sbumpc();

				// [string.io]/6.1
				if (Traits::eq_int_type(i, Traits::eof()))
				{
					state |= std::ios_base::eofbit;
					break;
				}
				
				++extracted;

				// [string.io]/6.2
				CharT const c = Traits::to_char_type(i);
				if (Traits::eq(c, delim))
				{
					break;
				}

				str.append(1, c);

				// [string.io]/6.3
				if (str.size() == str.max_size())
				{
					state |= std::ios_base::failbit;
					break;
				}
			}

			// [string.io]/8
			if (extracted == 0)
			{
				state |= std::ios_base::failbit;
			}
#if !defined(HAMON_NO_EXCEPTIONS)
		}
		catch (...)
		{
			state |= std::ios_base::badbit;
			is.setstate(state);	// TODO nothrow
			if (is.exceptions() & std::ios_base::badbit)
			{
				throw;
			}
		}
#endif
		is.setstate(state);
	}

	// [string.io]/9
	return is;
}

template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_istream<CharT, Traits>&
getline(
	std::basic_istream<CharT, Traits>&& is,
	basic_string<CharT, Traits2, Allocator>& str, CharT delim)
{
	return hamon::getline(is, str, delim);
}

template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_istream<CharT, Traits>&
getline(
	std::basic_istream<CharT, Traits>& is,
	basic_string<CharT, Traits2, Allocator>& str)
{
	// [string.io]/10
	return hamon::getline(is, str, is.widen('\n'));
}

template <typename CharT, typename Traits, typename Traits2, typename Allocator>
std::basic_istream<CharT, Traits>&
getline(
	std::basic_istream<CharT, Traits>&& is,
	basic_string<CharT, Traits2, Allocator>& str)
{
	// [string.io]/10
	return hamon::getline(is, str, is.widen('\n'));
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_GETLINE_HPP
