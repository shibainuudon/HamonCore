/**
 *	@file	range_size_t.hpp
 *
 *	@brief	ranges::range_size_t の定義
 */

#ifndef HAMON_RANGES_RANGE_SIZE_T_HPP
#define HAMON_RANGES_RANGE_SIZE_T_HPP

#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// [ranges.syn]
template <HAMON_CONSTRAINT(ranges::sized_range, R)>
using range_size_t = decltype(ranges::size(hamon::declval<R&>()));

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_RANGE_SIZE_T_HPP
