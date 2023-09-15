/**
 *	@file	u8string.hpp
 *
 *	@brief	u8string の定義
 */

#ifndef HAMON_STRING_U8STRING_HPP
#define HAMON_STRING_U8STRING_HPP

#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CHAR8_T)
using u8string = hamon::basic_string<char8_t>;
#endif

}	// namespace hamon

#endif // HAMON_STRING_U8STRING_HPP
