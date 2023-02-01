/**
 *	@file	subrange_kind.hpp
 *
 *	@brief	subrange_kind の定義
 */

#ifndef HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP
#define HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::subrange_kind;

}	// namespace ranges
}	// namespace hamon

#else

namespace hamon {
namespace ranges {

enum class subrange_kind : bool { unsized, sized };

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_SUBRANGE_KIND_HPP
