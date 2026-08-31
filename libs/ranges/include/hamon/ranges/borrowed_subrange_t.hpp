/**
 *	@file	borrowed_subrange_t.hpp
 *
 *	@brief	ranges::borrowed_subrange_t の定義
 */

#ifndef HAMON_RANGES_BORROWED_SUBRANGE_T_HPP
#define HAMON_RANGES_BORROWED_SUBRANGE_T_HPP

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/dangling.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

template <HAMON_CONSTRAINT(ranges::range, Range)>
using borrowed_subrange_t =
	hamon::conditional_t<
		ranges::borrowed_range<Range>,
		ranges::subrange<ranges::iterator_t<Range>>,
		ranges::dangling
	>;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_BORROWED_SUBRANGE_T_HPP
