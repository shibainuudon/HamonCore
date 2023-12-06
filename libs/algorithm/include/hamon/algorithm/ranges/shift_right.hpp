/**
 *	@file	shift_right.hpp
 *
 *	@brief	ranges::shift_right の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_SHIFT_RIGHT_HPP
#define HAMON_ALGORITHM_RANGES_SHIFT_RIGHT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_shift) && (__cpp_lib_shift >= 202202L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::shift_right;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/shift_right.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/permutable.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct shift_right_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::permutable, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent)
	>
	HAMON_CXX14_CONSTEXPR ranges::subrange<Iter>
	operator()(Iter first, Sent last, hamon::iter_difference_t<Iter> n) const
	{
		auto lasti = ranges::next(first, last);
		auto result = hamon::shift_right(first, lasti, n);
		return { hamon::move(result), hamon::move(lasti) };
	}

	template <HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range)>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, ranges::range_difference_t<Range> n) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		ranges::borrowed_subrange_t<Range>,
		hamon::permutable<ranges::iterator_t<Range>>)
	{
		return (*this)(ranges::begin(r), ranges::end(r), n);
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR shift_right_fn shift_right{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_SHIFT_RIGHT_HPP
