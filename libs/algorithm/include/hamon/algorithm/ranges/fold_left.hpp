/**
 *	@file	fold_left.hpp
 *
 *	@brief	ranges::fold_left の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_FOLD_LEFT_HPP
#define HAMON_ALGORITHM_RANGES_FOLD_LEFT_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM) &&	\
	defined(__cpp_lib_ranges_fold) && (__cpp_lib_ranges_fold >= 202207L)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::fold_left;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/algorithm/ranges/detail/indirectly_binary_left_foldable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/ref.hpp>
#include <hamon/iterator/concepts/input_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
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

struct fold_left_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_iterator, Iter),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Iter, Sent),
		typename T,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			T, Iter, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Iter first, Sent last, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, T, hamon::iter_reference_t<Iter>>>
	{
		using U = hamon::decay_t<hamon::invoke_result_t<F&, T, hamon::iter_reference_t<Iter>>>;
		if (first == last)
		{
			return U(hamon::move(init));
		}
		
		U accum = hamon::invoke(f, hamon::move(init), *first);
		for (++first; first != last; ++first)
		{
			accum = hamon::invoke(f, hamon::move(accum), *first);
		}

		return hamon::move(accum);
	}

	template <
		HAMON_CONSTRAINED_PARAM(ranges::input_range, Range),
		typename T,
		HAMON_CONSTRAINED_PARAM(
			ranges::detail::indirectly_binary_left_foldable,
			T, ranges::iterator_t<Range>, F)
	>
	HAMON_CXX14_CONSTEXPR auto
	operator()(Range&& r, T init, F f) const
	-> hamon::decay_t<hamon::invoke_result_t<F&, T, ranges::range_reference_t<Range>>>
	{
		return (*this)(
			ranges::begin(r), ranges::end(r),
			hamon::move(init),
			hamon::ref(f));
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
