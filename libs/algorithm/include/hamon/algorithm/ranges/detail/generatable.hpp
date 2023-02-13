/**
 *	@file	generatable.hpp
 *
 *	@brief	ranges::detail::generatable の定義
 */

#ifndef HAMON_ALGORITHM_RANGES_DETAIL_GENERATABLE_HPP
#define HAMON_ALGORITHM_RANGES_DETAIL_GENERATABLE_HPP

#include <hamon/concepts/invocable.hpp>
#include <hamon/iterator/concepts/indirectly_writable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/ranges/concepts/output_range.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

// generatable
template <typename Out, typename F>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept generatable =
	hamon::invocable<F&> &&
	hamon::indirectly_writable<Out, hamon::invoke_result_t<F&>>;
#else
using generatable = hamon::conjunction<
	hamon::invocable<F&>,
	hamon::indirectly_writable<Out, hamon::invoke_result_t<F&>>
>;
#endif

// generatable_range
template <typename Range, typename F>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
concept generatable_range =
	hamon::invocable<F&> &&
	ranges::output_range<Range, hamon::invoke_result_t<F&>>;
#else
using generatable_range = hamon::conjunction<
	hamon::invocable<F&>,
	ranges::output_range<Range, hamon::invoke_result_t<F&>>
>;
#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_ALGORITHM_RANGES_DETAIL_GENERATABLE_HPP
