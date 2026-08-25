/**
 *	@file	byteswap_impl.hpp
 *
 *	@brief	byteswap_impl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_DETAIL_BYTESWAP_IMPL_HPP
#define HAMON_BIT_DETAIL_BYTESWAP_IMPL_HPP

#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_MSVC)
#include <stdlib.h>	// _byteswap_ushort, _byteswap_ulong, _byteswap_uint64
#endif

namespace hamon
{
namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
byteswap_impl_u16(hamon::uint16_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap16)
	return __builtin_bswap16(value);
#else
#if defined(HAMON_MSVC)
	if (!hamon::is_constant_evaluated())
	{
		return _byteswap_ushort(value);
	}
#endif
	return static_cast<hamon::uint16_t>((value << 8) | (value >> 8));
#endif
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
byteswap_impl_u32(hamon::uint32_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap32)
	return __builtin_bswap32(value);
#else
#if defined(HAMON_MSVC)
	if (!hamon::is_constant_evaluated())
	{
		return _byteswap_ulong(value);
	}
#endif
	return
		 (value << 24) |
		((value <<  8) & 0x00FF0000) |
		((value >>  8) & 0x0000FF00) |
		 (value >> 24);
#endif
}

inline HAMON_CXX11_CONSTEXPR hamon::uint64_t
byteswap_impl_u64(hamon::uint64_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap64)
	return __builtin_bswap64(value);
#else
#if defined(HAMON_MSVC)
	if (!hamon::is_constant_evaluated())
	{
		return _byteswap_uint64(value);
	}
#endif
	return
		 (value << 56) |
		((value << 40) & 0x00FF000000000000) |
		((value << 24) & 0x0000FF0000000000) |
		((value <<  8) & 0x000000FF00000000) |
		((value >>  8) & 0x00000000FF000000) |
		((value >> 24) & 0x0000000000FF0000) |
		((value >> 40) & 0x000000000000FF00) |
		 (value >> 56);
#endif
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
byteswap_impl(T value, hamon::integral_constant<hamon::size_t, 1>) HAMON_NOEXCEPT
{
	return value;
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
byteswap_impl(T value, hamon::integral_constant<hamon::size_t, 2>) HAMON_NOEXCEPT
{
	return static_cast<T>(byteswap_impl_u16(static_cast<hamon::uint16_t>(value)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
byteswap_impl(T value, hamon::integral_constant<hamon::size_t, 4>) HAMON_NOEXCEPT
{
	return static_cast<T>(byteswap_impl_u32(static_cast<hamon::uint32_t>(value)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
byteswap_impl(T value, hamon::integral_constant<hamon::size_t, 8>) HAMON_NOEXCEPT
{
	return static_cast<T>(byteswap_impl_u64(static_cast<hamon::uint64_t>(value)));
}

template <typename T>
HAMON_CXX14_CONSTEXPR T
byteswap_impl(T value) HAMON_NOEXCEPT
{
	return byteswap_impl(value, hamon::integral_constant<hamon::size_t, sizeof(T)>{});
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIT_DETAIL_BYTESWAP_IMPL_HPP
