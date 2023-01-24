/**
 *	@file	as_writable_bytes.hpp
 *
 *	@brief	as_writable_bytes の定義
 */

#ifndef HAMON_SPAN_AS_WRITABLE_BYTES_HPP
#define HAMON_SPAN_AS_WRITABLE_BYTES_HPP

#include <hamon/span/config.hpp>

#if defined(HAMON_USE_STD_SPAN)

namespace hamon
{

using std::as_writable_bytes;

}	// namespace hamon

#else

#include <hamon/span/span.hpp>
#include <hamon/span/detail/as_bytes_extent.hpp>
#include <hamon/cstddef/byte.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <cstddef>
#include <type_traits>

namespace hamon
{

template <typename T, std::size_t Extent, typename = hamon::enable_if_t<!std::is_const<T>::value>>
inline span<hamon::byte, detail::as_bytes_extent<T, Extent>::value>
as_writable_bytes(span<T, Extent> s) HAMON_NOEXCEPT
{
	return span<hamon::byte, detail::as_bytes_extent<T, Extent>::value>
	{
		reinterpret_cast<hamon::byte*>(s.data()), s.size_bytes()
	};
}

}	// namespace hamon

#endif

#endif // HAMON_SPAN_AS_WRITABLE_BYTES_HPP
