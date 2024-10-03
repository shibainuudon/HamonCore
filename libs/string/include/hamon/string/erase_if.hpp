/**
 *	@file	erase_if.hpp
 *
 *	@brief	erase_if の定義
 */

#ifndef HAMON_STRING_ERASE_IF_HPP
#define HAMON_STRING_ERASE_IF_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_STRING) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002)

#include <string>

namespace hamon
{

using std::erase_if;

}	// namespace hamon

#else

#include <hamon/algorithm/remove_if.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 23.4.4.5 Erasure[string.erasure]

template <typename CharT, typename Traits, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hamon::basic_string<CharT, Traits, Allocator>::size_type
erase_if(hamon::basic_string<CharT, Traits, Allocator>& str, Predicate pred)
{
	auto const osz = str.size();
	str.erase(hamon::remove_if(str.begin(), str.end(), pred), str.end());
	return osz - str.size();
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_ERASE_IF_HPP
