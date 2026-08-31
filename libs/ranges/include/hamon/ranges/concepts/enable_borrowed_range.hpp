/**
 *	@file	enable_borrowed_range.hpp
 *
 *	@brief	enable_borrowed_range の定義
 */

#ifndef HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
#define HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP

#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{

// [range.range]/6

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool enable_borrowed_range = false;

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_CONCEPTS_ENABLE_BORROWED_RANGE_HPP
