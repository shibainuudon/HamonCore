/**
 *	@file	fold_left.hpp
 *
 *	@brief	ranges::fold_left の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_LEFT_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_LEFT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_left;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/fold_left_with_iter.hpp>
#include <hamon/algorithm/ranges/detail/indirectly_binary_left_foldable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.6.18 Fold[alg.fold]

struct fold_left_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename T = hamon::iter_value_t<I>,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			T, I, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(I first, S last, T init, F f) const
	-> decltype(ranges::fold_left_with_iter(
			hamon::move(first), last, hamon::move(init), hamon::ref(f)).value)
	{
		// [alg.fold]/1
		return ranges::fold_left_with_iter(
			hamon::move(first), last, hamon::move(init), hamon::ref(f)).value;
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, R),
		typename T = ranges::range_value_t<R>,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			T, ranges::iterator_t<R>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, T init, F f) const
	-> decltype(ranges::fold_left_with_iter(
			ranges::begin(r), ranges::end(r), hamon::move(init), hamon::ref(f)).value)
	{
		// [alg.fold]/1
		return ranges::fold_left_with_iter(
			ranges::begin(r), ranges::end(r), hamon::move(init), hamon::ref(f)).value;
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fold_left_fn fold_left{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOLD_LEFT_HPP
