/**
 *	@file	u16string.hpp
 *
 *	@brief	u16string の定義
 */

#ifndef HAMON_STRING_U16STRING_HPP
#define HAMON_STRING_U16STRING_HPP

#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX11_CHAR16_T)
using u16string = hamon::basic_string<char16_t>;
#endif

}	// namespace hamon

#endif // HAMON_STRING_U16STRING_HPP
