/**
 *	@file	fold_left_first_with_iter.hpp
 *
 *	@brief	ranges::fold_left_first_with_iter の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_LEFT_FIRST_WITH_ITER_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_LEFT_FIRST_WITH_ITER_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_left_first_with_iter;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/fold_left.hpp>
#include <hamon/algorithm/ranges/detail/indirectly_binary_left_foldable.hpp>
#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/algorithm/ranges/in_value_result.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
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

template <typename I, typename T>
using fold_left_first_with_iter_result = ranges::in_value_result<I, T>;

struct fold_left_first_with_iter_fn
{
private:
	template <typename O, typename I, typename S, typename F,
		typename U = decltype(ranges::fold_left(
			hamon::declval<I>(),
			hamon::declval<S>(),
			hamon::declval<hamon::iter_value_t<I>>(),
			hamon::declval<F>())),
		typename Ret =
			ranges::fold_left_first_with_iter_result<O, hamon::optional<U>>
	>
	HAMON_CXX14_CONSTEXPR Ret
	impl(I&& first, S&& last, F f) const
	{
		if (first == last)
		{
			return Ret{hamon::move(first), hamon::optional<U>()};
		}

		hamon::optional<U> init(hamon::in_place, *first);
		for (++first; first != last; ++first)
		{
			*init = hamon::invoke(f, hamon::move(*init), *first);
		}

		return Ret{hamon::move(first), hamon::move(init)};
	}

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			hamon::iter_value_t<Iter>, Iter, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, F f) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		decltype(impl<Iter>(
			hamon::move(first), hamon::move(last), hamon::ref(f))),
		hamon::constructible_from<
			hamon::iter_value_t<Iter>,
			hamon::iter_reference_t<Iter>>)
	{
		return impl<Iter>(
			hamon::move(first), hamon::move(last), hamon::ref(f));
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			ranges::range_value_t<Range>, ranges::iterator_t<Range>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, F f) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		decltype(impl<ranges::borrowed_iterator_t<Range>>(
			ranges::begin(r), ranges::end(r), hamon::ref(f))),
		hamon::constructible_from<
			ranges::range_value_t<Range>,
			ranges::range_reference_t<Range>>)
	{
		return impl<ranges::borrowed_iterator_t<Range>>(
			ranges::begin(r), ranges::end(r), hamon::ref(f));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
fold_left_first_with_iter_fn fold_left_first_with_iter{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOLD_LEFT_FIRST_WITH_ITER_HPP
