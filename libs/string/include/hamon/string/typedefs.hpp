/**
 *	@file	typedefs.hpp
 *
 *	@brief
 */

#ifndef HAMON_STRING_TYPEDEFS_HPP
#define HAMON_STRING_TYPEDEFS_HPP

#include <hamon/string/basic_string_fwd.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// basic_string typedef-names

using string    = hamon::basic_string<char>;
#if defined(HAMON_HAS_CXX20_CHAR8_T)
using u8string  = hamon::basic_string<char8_t>;
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
using u16string = hamon::basic_string<char16_t>;
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
using u32string = hamon::basic_string<char32_t>;
#endif
using wstring   = hamon::basic_string<wchar_t>;

}	// namespace hamon

#endif // HAMON_STRING_TYPEDEFS_HPP
