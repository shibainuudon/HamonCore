/**
 *	@file	range_difference_t.hpp
 *
 *	@brief	ranges::range_difference_t の定義
 */

#ifndef HAMON_RANGES_RANGE_DIFFERENCE_T_HPP
#define HAMON_RANGES_RANGE_DIFFERENCE_T_HPP

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// [ranges.syn]
template <HAMON_CONSTRAINT(ranges::range, R)>
using range_difference_t = hamon::iter_difference_t<ranges::iterator_t<R>>;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_RANGE_DIFFERENCE_T_HPP
