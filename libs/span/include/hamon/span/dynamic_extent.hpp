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

#include <hamon/cstddef/size_t.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// [span.syn]
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR hamon::size_t
dynamic_extent = hamon::numeric_limits<hamon::size_t>::max();

}	// namespace hamon

#endif

#endif // HAMON_SPAN_DYNAMIC_EXTENT_HPP
