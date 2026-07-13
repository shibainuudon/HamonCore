/**
 *	@file	enable_borrowed_range.hpp
 *
 *	@brief	enable_borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP

#include <hamon/ranges/config.hpp>

namespace hamon
{
namespace ranges
{

// [range.range]/6

#if defined(HAMON_USE_STD_RANGES)

using std::ranges::enable_borrowed_range;

#else

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool enable_borrowed_range = false;

#endif

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
