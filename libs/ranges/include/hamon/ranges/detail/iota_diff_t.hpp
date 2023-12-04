/**
 *	@file	iota_diff_t.hpp
 *
 *	@brief	iota_diff_t の定義
 */

#ifndef HAMON_RANGES_DETAIL_IOTA_DIFF_T_HPP
#define HAMON_RANGES_DETAIL_IOTA_DIFF_T_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_integral.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.iota.view]/1
template <typename W>
using iota_diff_t =
	hamon::conditional_t<!hamon::is_integral<W>::value,
		hamon::iter_difference_t<W>,	// [range.iota.view]/1.1
	hamon::conditional_t<(sizeof(hamon::iter_difference_t<W>) > sizeof(W)),
		hamon::iter_difference_t<W>,	// [range.iota.view]/1.1
	hamon::conditional_t<(sizeof(hamon::ptrdiff_t) > sizeof(W)),
		hamon::ptrdiff_t,				// [range.iota.view]/1.2, 1,3	// TODO
		long long
	>>>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_IOTA_DIFF_T_HPP
