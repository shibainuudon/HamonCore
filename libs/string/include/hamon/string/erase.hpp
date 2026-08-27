/**
 *	@file	erase.hpp
 *
 *	@brief	erase の定義
 */

#ifndef HAMON_STRING_ERASE_HPP
#define HAMON_STRING_ERASE_HPP

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

#endif // HAMON_STRING_ERASE_HPP
