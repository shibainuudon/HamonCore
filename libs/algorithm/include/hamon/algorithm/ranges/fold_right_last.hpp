﻿/**
 *	@file	fold_right_last.hpp
 *
 *	@brief	ranges::fold_right_last の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_RIGHT_LAST_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_RIGHT_LAST_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_right_last;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/fold_right.hpp>
#include <hamon/algorithm/ranges/detail/indirectly_binary_right_foldable.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/in_place_t.hpp>
#include <hamon/optional.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.6.18 Fold[alg.fold]

struct fold_right_last_fn
{
private:
	template <
		typename I, typename S, typename F,
		// [alg.fold]/4
		typename U = decltype(ranges::fold_right(
			hamon::declval<I>(),
			hamon::declval<S>(),
			hamon::declval<hamon::iter_value_t<I>>(),
			hamon::declval<F>()))
	>
	HAMON_CXX14_CONSTEXPR hamon::optional<U>
	impl(I first, S last, F f) const
	{
		// [alg.fold]/5
		if (first == last)
		{
			return hamon::optional<U>();
		}

		I tail = ranges::prev(ranges::next(first, hamon::move(last)));
		return hamon::optional<U>(hamon::in_place,
			ranges::fold_right(
				hamon::move(first),
				tail,
				hamon::iter_value_t<I>(*tail),
				hamon::move(f)));
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			hamon::iter_value_t<I>, I, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(I first, S last, F f) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		decltype(impl(hamon::move(first), hamon::move(last), hamon::ref(f))),
		hamon::constructible_from<
			hamon::iter_value_t<I>,
			hamon::iter_reference_t<I>>)
	{
		return impl(hamon::move(first), hamon::move(last), hamon::ref(f));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::bidirectional_range, R),
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			ranges::range_value_t<R>, ranges::iterator_t<R>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, F f) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		decltype((*this)(ranges::begin(r), ranges::end(r), hamon::ref(f))),
		hamon::constructible_from<
			ranges::range_value_t<R>,
			ranges::range_reference_t<R>>)
	{
		return (*this)(ranges::begin(r), ranges::end(r), hamon::ref(f));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fold_right_last_fn fold_right_last{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOLD_RIGHT_LAST_HPP
