/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_STRING_ERASE_HPP
#define HAMON_STRING_ERASE_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_STRING) && \
	defined(__cpp_lib_erase_if) && (__cpp_lib_erase_if >= 202002) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <string>

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

// 23.4.4.5 Erasure[string.erasure]

template <typename CharT, typename Traits, typename Allocator, typename U = CharT>
HAMON_CXX14_CONSTEXPR
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
