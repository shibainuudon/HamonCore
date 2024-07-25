/**
 *	@file	nothrow_forward_iterator.hpp
 *
 *	@brief	nothrow_forward_iterator を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_ITERATOR_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_ITERATOR_HPP

#include <hamon/memory/ranges/detail/nothrow_input_iterator.hpp>
#include <hamon/memory/ranges/detail/nothrow_sentinel_for.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
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

template <typename I>
concept nothrow_forward_iterator =
	hamon::ranges::detail::nothrow_input_iterator<I> &&
	hamon::forward_iterator<I> &&
	hamon::ranges::detail::nothrow_sentinel_for<I, I>;

#else

template <typename I>
using nothrow_forward_iterator = hamon::conjunction<
	hamon::ranges::detail::nothrow_input_iterator<I>,
	hamon::forward_iterator<I>,
	hamon::ranges::detail::nothrow_sentinel_for<I, I>>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_ITERATOR_HPP
