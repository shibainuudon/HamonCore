/**
 *	@file	subrange_kind.hpp
 *
 *	@brief	subrange_kind の定義
 */

#ifndef HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP
#define HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP

#include <hamon/ranges/config.hpp>

namespace hamon {
namespace ranges {

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::subrange_kind;

#else

enum class subrange_kind : bool { unsized, sized };

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP
