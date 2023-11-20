/**
 *	@file	as_bytes.hpp
 *
 *	@brief	as_bytes の定義
 */

#ifndef HAMON_SPAN_AS_BYTES_HPP
#define HAMON_SPAN_AS_BYTES_HPP

#include <hamon/span/config.hpp>

#if defined(HAMON_USE_STD_SPAN)

namespace hamon
{

using std::as_bytes;

}	// namespace hamon

#else

#include <hamon/span/span.hpp>
#include <hamon/span/detail/as_bytes_extent.hpp>
#include <hamon/cstddef/byte.hpp>
#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// [span.objectrep]
template <typename T, hamon::size_t Extent>
inline span<hamon::byte const, detail::as_bytes_extent<T, Extent>::value>
as_bytes(span<T, Extent> s) HAMON_NOEXCEPT
{
	return span<hamon::byte const, detail::as_bytes_extent<T, Extent>::value>
	{
		reinterpret_cast<hamon::byte const*>(s.data()), s.size_bytes()
	};
}

}	// namespace hamon

#endif

#endif // HAMON_SPAN_AS_BYTES_HPP
