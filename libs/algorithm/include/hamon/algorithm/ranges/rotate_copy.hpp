﻿/**
 *	@file	rotate_copy.hpp
 *
 *	@brief	ranges::rotate_copy の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_ROTATE_COPY_HPP
#define HAMON_ALGORITHM_RANGES_ROTATE_COPY_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::rotate_copy;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/copy.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/indirectly_copyable.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <typename Iter, typename Out>
using rotate_copy_result = in_out_result<Iter, Out>;

struct rotate_copy_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::forward_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Iter middle, Sent last, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		rotate_copy_result<Iter HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<Iter, Out>)
	{
		auto copy1 = ranges::copy(
			middle,
			hamon::move(last),
			hamon::move(result));
		auto copy2 = ranges::copy(
			hamon::move(first),
			hamon::move(middle),
			hamon::move(copy1.out));
		return { hamon::move(copy1.in), hamon::move(copy2.out) };
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::forward_range, Range),
		HAMON_CONSTRAINED_PARAM(hamon::weakly_incrementable, Out)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, ranges::iterator_t<Range> middle, Out result) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		rotate_copy_result<ranges::borrowed_iterator_t<Range> HAMON_PP_COMMA() Out>,
		hamon::indirectly_copyable<ranges::iterator_t<Range>, Out>)
	{
		return (*this)(
			ranges::begin(r),
			hamon::move(middle),
			ranges::end(r),
			hamon::move(result));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR rotate_copy_fn rotate_copy{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_ROTATE_COPY_HPP
