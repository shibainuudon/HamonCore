/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_STRING_ERASE_HPP
#define HAMON_STRING_ERASE_HPP

//#include <hamon/string/config.hpp>
#include <string>

//#if 1//defined(HAMON_USE_STD_STRING)	// TODO
#if defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

namespace hamon
{

using std::erase;

}	// namespace hamon

#else

#include <hamon/algorithm/remove.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

template <typename CharT, typename Traits, typename Allocator, typename U>
inline HAMON_CXX14_CONSTEXPR
typename hamon::basic_string<CharT, Traits, Allocator>::size_type
erase(hamon::basic_string<CharT, Traits, Allocator>& str, U const& value)
{
	auto const osz = str.size();
	str.erase(hamon::remove(str.begin(), str.end(), value), str.end());
	return osz - str.size();
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_ERASE_HPP
