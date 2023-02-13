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

#include <hamon/algorithm/ranges/detail/return_type_requires_clauses.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/and.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/invoke_result.hpp>
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
	>
	HAMON_CXX14_CONSTEXPR auto operator()(
		Out first, hamon::iter_difference_t<Out> n, F gen) const
	HAMON_RETURN_TYPE_REQUIRES_CLAUSES(
		Out,
		HAMON_CONCEPTS_AND(
			hamon::invocable<F&>,
			hamon::indirectly_writable<Out HAMON_PP_COMMA() hamon::invoke_result_t<F&>>))
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
