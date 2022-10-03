/**
 *	@file	range_value_t.hpp
 *
 *	@brief	ranges::range_value_t の定義
 */

#ifndef HAMON_RANGES_RANGE_VALUE_T_HPP
#define HAMON_RANGES_RANGE_VALUE_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::range_value_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::range, Range)>
using range_value_t = hamon::iter_value_t<ranges::iterator_t<Range>>;

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_RANGE_VALUE_T_HPP
