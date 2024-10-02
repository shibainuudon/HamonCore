/**
 *	@file	fold_right.hpp
 *
 *	@brief	ranges::fold_right の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_RIGHT_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_RIGHT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L) && \
	defined(__cpp_lib_algorithm_default_value_type) && (__cpp_lib_algorithm_default_value_type >= 202403L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_right;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/indirectly_binary_right_foldable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/bidirectional_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

// 27.6.18 Fold[alg.fold]

struct fold_right_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, I),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, I, S),
		typename T = hamon::iter_value_t<I>,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			T, I, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(I first, S last, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, hamon::iter_reference_t<I>, T>>
	{
		// [alg.fold]/3
		using U = hamon::decay_t<hamon::invoke_result_t<F&, hamon::iter_reference_t<I>, T>>;
		if (first == last)
		{
			return U(hamon::move(init));
		}

		I tail = ranges::next(first, last);
		U accum = hamon::invoke(f, *--tail, hamon::move(init));
		while (first != tail)
		{
			accum = hamon::invoke(f, *--tail, hamon::move(accum));
		}

		return hamon::move(accum);
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::bidirectional_range, R),
		typename T = ranges::range_value_t<R>,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			T, ranges::iterator_t<R>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(R&& r, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, ranges::range_reference_t<R>, T>>
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(init),
			hamon::ref(f));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR fold_right_fn fold_right{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_FOLD_RIGHT_HPP
