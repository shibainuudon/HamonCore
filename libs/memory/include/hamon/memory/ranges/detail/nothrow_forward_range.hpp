/**
 *	@file	nothrow_forward_range.hpp
 *
 *	@brief	nothrow_forward_range を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP

#include <hamon/memory/ranges/detail/nothrow_input_range.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/ranges/iterator_t.hpp>
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

template <typename R>
concept nothrow_forward_range =
	hamon::ranges::detail::nothrow_input_range<R> &&
	hamon::ranges::detail::nothrow_forward_iterator<hamon::ranges::iterator_t<R>>;

#else

template <typename R>
using nothrow_forward_range = hamon::conjunction<
	hamon::ranges::detail::nothrow_input_range<R>,
	hamon::ranges::detail::nothrow_forward_iterator<hamon::ranges::iterator_t<R>>>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP
