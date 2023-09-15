/**
 *	@file	u32string.hpp
 *
 *	@brief	u32string の定義
 */

#ifndef HAMON_STRING_U32STRING_HPP
#define HAMON_STRING_U32STRING_HPP

#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX11_CHAR32_T)
using u32string = hamon::basic_string<char32_t>;
#endif

}	// namespace hamon

#endif // HAMON_STRING_U32STRING_HPP
