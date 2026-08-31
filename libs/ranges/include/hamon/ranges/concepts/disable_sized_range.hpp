/**
 *	@file	disable_sized_range.hpp
 *
 *	@brief	disable_sized_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP

#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

// [range.sized]/3

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool disable_sized_range = false;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_DISABLE_SIZED_RANGE_HPP
