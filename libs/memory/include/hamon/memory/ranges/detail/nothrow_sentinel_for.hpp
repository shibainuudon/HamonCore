/**
 *	@file	nothrow_sentinel_for.hpp
 *
 *	@brief	nothrow_sentinel_for を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_SENTINEL_FOR_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_SENTINEL_FOR_HPP

#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.2 Special memory concepts[special.mem.concepts]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [special.mem.concepts]/4
template <typename S, typename I>
concept nothrow_sentinel_for = hamon::sentinel_for<S, I>;

#else

template <typename S, typename I>
using nothrow_sentinel_for = hamon::sentinel_for<S, I>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_SENTINEL_FOR_HPP
