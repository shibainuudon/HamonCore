/**
 *	@file	as_bytes_extent.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_DETAIL_AS_BYTES_EXTENT_HPP
#define HAMON_SPAN_DETAIL_AS_BYTES_EXTENT_HPP

#include <hamon/span/dynamic_extent.hpp>
#include <cstddef>

namespace hamon
{

namespace detail
{

template <typename T, std::size_t Extent>
struct as_bytes_extent
{
	static const std::size_t value = Extent * sizeof(T);
};

template <typename T>
struct as_bytes_extent<T, hamon::dynamic_extent>
{
	static const std::size_t value = hamon::dynamic_extent;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_AS_BYTES_EXTENT_HPP
