/**
 *	@file	wstring_view.hpp
 *
 *	@brief	wstring_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_WSTRING_VIEW_HPP
#define HAMON_STRING_VIEW_WSTRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>

namespace hamon
{

using wstring_view = hamon::basic_string_view<wchar_t>;

}	// namespace hamon

#endif // HAMON_STRING_VIEW_WSTRING_VIEW_HPP
