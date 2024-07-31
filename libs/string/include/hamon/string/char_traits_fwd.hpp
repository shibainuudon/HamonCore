/**
 *	@file	char_traits_fwd.hpp
 *
 *	@brief	char_traits クラステンプレートの前方宣言
 */

#ifndef HAMON_STRING_CHAR_TRAITS_FWD_HPP
#define HAMON_STRING_CHAR_TRAITS_FWD_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_CHAR_TRAITS)

#include <string>

namespace hamon
{

using std::char_traits;

}	// namespace hamon

#else

namespace hamon
{

template <typename CharT>
struct char_traits;

}	// namespace hamon

#endif	// defined(HAMON_USE_STD_CHAR_TRAITS)

#endif // HAMON_STRING_CHAR_TRAITS_FWD_HPP
