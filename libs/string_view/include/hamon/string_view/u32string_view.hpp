/**
 *	@file	u32string_view.hpp
 *
 *	@brief	u32string_view クラスの定義
 */

#ifndef HAMON_STRING_VIEW_U32STRING_VIEW_HPP
#define HAMON_STRING_VIEW_U32STRING_VIEW_HPP

#include <hamon/string_view/basic_string_view.hpp>
#include <hamon/config.hpp>

namespace hamon
{

#if defined(HAMON_HAS_CXX11_CHAR32_T)
using u32string_view = hamon::basic_string_view<char32_t>;
#endif

}	// namespace hamon

#endif // HAMON_STRING_VIEW_U32STRING_VIEW_HPP
