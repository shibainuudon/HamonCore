/**
 *	@file	dynamic_extent.hpp
 *
 *	@brief	dynamic_extent の定義
 */

#ifndef HAMON_SPAN_DYNAMIC_EXTENT_HPP
#define HAMON_SPAN_DYNAMIC_EXTENT_HPP

#include <hamon/span/config.hpp>

#if defined(HAMON_USE_STD_SPAN)

namespace hamon
{

using std::dynamic_extent;

}	// namespace hamon

#else

#include <hamon/config.hpp>
#include <cstddef>
#include <limits>

namespace hamon
{

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR std::size_t
dynamic_extent = std::numeric_limits<std::size_t>::max();

}	// namespace hamon

#endif

#endif // HAMON_SPAN_DYNAMIC_EXTENT_HPP
