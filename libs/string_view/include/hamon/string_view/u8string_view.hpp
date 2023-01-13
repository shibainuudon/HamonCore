/**
 *	@file	u8string_view.hpp
 *
 *	@brief	u8string_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_U8STRING_VIEW_HPP
#define HAMON_STRING_VIEW_U8STRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CHAR8_T)
using u8string_view = hamon::basic_string_view<char8_t>;
#endif

}	// namespace hamon

#endif // HAMON_STRING_VIEW_U8STRING_VIEW_HPP
