/**
 *	@file	span_fwd.hpp
 *
 *	@brief	span の前方宣言
 */

#ifndef HAMON_SPAN_SPAN_FWD_HPP
#define HAMON_SPAN_SPAN_FWD_HPP

#include <hamon/span/config.hpp>

#if defined(HAMON_USE_STD_SPAN)

namespace hamon
{

using std::span;

}	// namespace hamon

#else

#include <hamon/span/dynamic_extent.hpp>
#include <cstddef>

namespace hamon
{

template <typename T, std::size_t Extent = hamon::dynamic_extent>
class span;

}	// namespace hamon

#endif

#endif // HAMON_SPAN_SPAN_FWD_HPP
