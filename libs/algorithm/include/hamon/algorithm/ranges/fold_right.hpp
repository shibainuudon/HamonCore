/**
 *	@file	fold_right.hpp
 *
 *	@brief	ranges::fold_right の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_RIGHT_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_RIGHT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L)

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
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
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

struct fold_right_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::bidirectional_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			T, Iter, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, hamon::iter_reference_t<Iter>, T>>
	{
		using U = hamon::decay_t<hamon::invoke_result_t<F&, hamon::iter_reference_t<Iter>, T>>;
		if (first == last)
		{
			return U(hamon::move(init));
		}

		Iter tail = ranges::next(first, last);
		U accum = hamon::invoke(f, *--tail, hamon::move(init));
		while (first != tail)
		{
			accum = hamon::invoke(f, *--tail, hamon::move(accum));
		}

		return hamon::move(accum);
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::bidirectional_range, Range),
		typename T,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_right_foldable,
			T, ranges::iterator_t<Range>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, ranges::range_reference_t<Range>, T>>
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
