/**
 *	@file	disable_sized_range.hpp
 *
 *	@brief	disable_sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP

#include <hamon/ranges/config.hpp>

namespace hamon
{
namespace ranges
{

// [range.sized]/3

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::disable_sized_range;

#else

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disable_sized_range = false;

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
