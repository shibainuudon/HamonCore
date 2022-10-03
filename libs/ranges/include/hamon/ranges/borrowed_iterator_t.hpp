/**
 *	@file	borrowed_iterator_t.hpp
 *
 *	@brief	ranges::borrowed_iterator_t の定義
 */

#ifndef HAMON_RANGES_BORROWED_ITERATOR_T_HPP
#define HAMON_RANGES_BORROWED_ITERATOR_T_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::borrowed_iterator_t;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/dangling.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINED_PARAM(ranges::range, Range)>
using borrowed_iterator_t =
	hamon::conditional_t<
		ranges::borrowed_range_t<Range>::value,
		ranges::iterator_t<Range>,
		ranges::dangling
	>;

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_BORROWED_ITERATOR_T_HPP
