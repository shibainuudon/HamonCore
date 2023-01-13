/**
 *	@file	string_view.hpp
 *
 *	@brief	string_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_STRING_VIEW_HPP
#define HAMON_STRING_VIEW_STRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>

namespace hamon
{

using string_view = hamon::basic_string_view<char>;

}	// namespace hamon

#endif // HAMON_STRING_VIEW_STRING_VIEW_HPP
