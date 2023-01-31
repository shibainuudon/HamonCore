/**
 *	@file	generate_n.hpp
 *
 *	@brief	ranges::generate_n の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_GENERATE_N_HPP
#define HAMON_ALGORITHM_RANGES_GENERATE_N_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::generate_n;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

struct generate_n_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, Out),
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F)
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::invocable<F&>,
			hamon::indirectly_writable<Out, hamon::invoke_result_t<F&>>
		>::value>
	>
#else
	>
	requires hamon::invocable<F&> &&
		hamon::indirectly_writable<Out, hamon::invoke_result_t<F&>>
#endif
	HAMON_CXX14_CONSTEXPR Out operator()(
		Out first, hamon::iter_difference_t<Out> n, F gen) const
	{
		for (; n > 0; --n, (void)++first)
		{
			*first = hamon::invoke(gen);
		}

		return first;
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR generate_n_fn generate_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_GENERATE_N_HPP
