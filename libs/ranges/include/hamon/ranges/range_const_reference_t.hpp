/**
 *	@file	range_const_reference_t.hpp
 *
 *	@brief	ranges::range_const_reference_t の定義
 */

#ifndef HAMON_RANGES_RANGE_CONST_REFERENCE_T_HPP
#define HAMON_RANGES_RANGE_CONST_REFERENCE_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) &&	\
	defined(__cpp_lib_ranges_as_const) && (__cpp_lib_ranges_as_const >= 202207L)

namespace hamon {
namespace ranges {

using std::ranges::range_const_reference_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::range, R)>
using range_const_reference_t = hamon::iter_const_reference_t<hamon::ranges::iterator_t<R>>;

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_RANGE_CONST_REFERENCE_T_HPP
