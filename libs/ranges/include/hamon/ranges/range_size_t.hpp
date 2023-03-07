/**
 *	@file	range_size_t.hpp
 *
 *	@brief	ranges::range_size_t の定義
 */

#ifndef HAMON_RANGES_RANGE_SIZE_T_HPP
#define HAMON_RANGES_RANGE_SIZE_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::range_size_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::sized_range, Range)>
using range_size_t = decltype(ranges::size(hamon::declval<Range&>()));

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_RANGE_SIZE_T_HPP
