/**
 *	@file	nothrow_input_range.hpp
 *
 *	@brief	nothrow_input_range を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_RANGE_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_RANGE_HPP

#include <hamon/memory/ranges/detail/nothrow_input_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_sentinel_for.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.2 Special memory concepts[special.mem.concepts]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [special.mem.concepts]/6
template <typename R>
concept nothrow_input_range =
	hamon::ranges::range<R> &&
	hamon::ranges::detail::nothrow_input_iterator<hamon::ranges::iterator_t<R>> &&
	hamon::ranges::detail::nothrow_sentinel_for<hamon::ranges::sentinel_t<R>, hamon::ranges::iterator_t<R>>;

#else

template <typename R>
using nothrow_input_range = hamon::conjunction<
	hamon::ranges::range<R>,
	hamon::ranges::detail::nothrow_input_iterator<hamon::ranges::iterator_t<R>>,
	hamon::ranges::detail::nothrow_sentinel_for<hamon::ranges::sentinel_t<R>, hamon::ranges::iterator_t<R>>>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_INPUT_RANGE_HPP
