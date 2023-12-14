/**
 *	@file	maybe_const.hpp
 *
 *	@brief	maybe_const の定義
 */

#ifndef HAMON_RANGES_DETAIL_MAYBE_CONST_HPP
#define HAMON_RANGES_DETAIL_MAYBE_CONST_HPP

#include <hamon/type_traits/conditional.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [ranges.syn]

template <bool Const, class T>
using maybe_const = hamon::conditional_t<Const, const T, T>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_MAYBE_CONST_HPP
