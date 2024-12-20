﻿/**
 *	@file	fold_left_with_iter.hpp
 *
 *	@brief	ranges::fold_left_with_iter の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_LEFT_WITH_ITER_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_LEFT_WITH_ITER_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_left_with_iter;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/indirectly_binary_left_foldable.hpp>
#include <hamon/algorithm/ranges/in_value_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.6.18 Fold[alg.fold]

template <typename I, typename T>
using fold_left_with_iter_result = ranges::in_value_result<I, T>;

struct fold_left_with_iter_fn
{
private:
	template <typename O, typename I, typename S, typename T, typename F,
		// [alg.fold]/6
		typename U = hamon::decay_t<
			hamon::invoke_result_t<F&, T, hamon::iter_reference_t<I>>>,
		typename Ret = ranges::fold_left_with_iter_result<O, U>
	>
	HAMON_CXX14_CONSTEXPR Ret
	impl(I&& first, S&& last, T&& init, F f) const
	{
		// [alg.fold]/7
		if (first == last)
		{
			return Ret{hamon::move(first), U(hamon::move(init))};
		}

		U accum = hamon::invoke(f, hamon::move(init), *first);
		for (++first; first != last; ++first)
		{
			accum = hamon::invoke(f, hamon::move(accum), *first);
		}

		return Ret{hamon::move(first), hamon::move(accum)};
	}

public:
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
	->decltype(impl<I>(
			hamon::move(first), hamon::move(last), hamon::move(init), hamon::ref(f)))
	{
		return impl<I>(
			hamon::move(first), hamon::move(last), hamon::move(init), hamon::ref(f));
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
	->decltype(impl<ranges::borrowed_iterator_t<R>>(
			ranges::begin(r), ranges::end(r), hamon::move(init), hamon::ref(f)))
	{
		return impl<ranges::borrowed_iterator_t<R>>(
			ranges::begin(r), ranges::end(r), hamon::move(init), hamon::ref(f));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fold_left_with_iter_fn fold_left_with_iter{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOLD_LEFT_WITH_ITER_HPP
