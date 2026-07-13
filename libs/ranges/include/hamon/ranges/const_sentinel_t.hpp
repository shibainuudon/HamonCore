/**
 *	@file	const_sentinel_t.hpp
 *
 *	@brief	ranges::const_sentinel_t の定義
 */

#ifndef HAMON_RANGES_CONST_SENTINEL_T_HPP
#define HAMON_RANGES_CONST_SENTINEL_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::const_sentinel_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/cend.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon {
namespace ranges {

// [ranges.syn]
template <HAMON_CONSTRAINT(ranges::range, R)>
using const_sentinel_t = decltype(ranges::cend(hamon::declval<R&>()));

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_CONST_SENTINEL_T_HPP
