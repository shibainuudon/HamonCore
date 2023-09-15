/**
 *	@file	wstring.hpp
 *
 *	@brief	wstring の定義
 */

#ifndef HAMON_STRING_WSTRING_HPP
#define HAMON_STRING_WSTRING_HPP

#include <hamon/string/basic_string.hpp>

namespace hamon
{

using wstring = hamon::basic_string<wchar_t>;

}	// namespace hamon

#endif // HAMON_STRING_WSTRING_HPP
