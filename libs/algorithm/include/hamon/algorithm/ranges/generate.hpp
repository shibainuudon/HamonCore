/**
 *	@file	generate.hpp
 *
 *	@brief	ranges::generate の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_GENERATE_HPP
#define HAMON_ALGORITHM_RANGES_GENERATE_HPP

#include <hamon/algorithm/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ALGORITHM)

#include <algorithm>

namespace hamon
{

namespace ranges
{

using std::ranges::generate;

}	// namespace ranges

}	// namespace hamon

#else

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/invocable.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/ranges/concepts/output_range.hpp>
#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

struct generate_fn
{
	template <
		HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, Out),
		HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, Out, Sent),
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
		Out first, Sent last, F gen) const
	{
		for (; first != last; ++first)
		{
			*first = hamon::invoke(gen);
		}
		return first;
	}

	template <
		typename Range,
		HAMON_CONSTRAINED_PARAM(hamon::copy_constructible, F)
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, typename = hamon::enable_if_t<hamon::conjunction<
			hamon::invocable<F&>,
			ranges::output_range<Range, hamon::invoke_result_t<F&>>
		>::value>
	>
#else
	>
	requires hamon::invocable<F&> &&
		ranges::output_range<Range, hamon::invoke_result_t<F&>>
#endif
	HAMON_CXX14_CONSTEXPR ranges::borrowed_iterator_t<Range>
	operator()(Range&& r, F gen) const
	{
		return (*this)(ranges::begin(r), ranges::end(r), std::move(gen));
	}
};

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR generate_fn generate{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ALGORITHM_RANGES_GENERATE_HPP
