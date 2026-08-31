/**
 *	@file	range_common_reference_t.hpp
 *
 *	@brief	ranges::range_common_reference_t の定義
 */

#ifndef HAMON_RANGES_RANGE_COMMON_REFERENCE_T_HPP
#define HAMON_RANGES_RANGE_COMMON_REFERENCE_T_HPP

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/iterator/iter_common_reference_t.hpp>

namespace hamon {
namespace ranges {

// [ranges.syn]
template <HAMON_CONSTRAINT(ranges::range, R)>
using range_common_reference_t = hamon::iter_common_reference_t<ranges::iterator_t<R>>;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_RANGE_COMMON_REFERENCE_T_HPP
