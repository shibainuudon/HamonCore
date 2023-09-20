/**
 *	@file	byteswap.hpp
 *
 *	@brief	byteswap 関数テンプレートの定義
 */

#ifndef HAMON_BIT_BYTESWAP_HPP
#define HAMON_BIT_BYTESWAP_HPP

#include <hamon/bit/config.hpp>

#if defined(__cpp_lib_byteswap) && (__cpp_lib_byteswap >= 202110L)

#include <bit>

namespace hamon
{

using std::byteswap;

}	// namespace hamon

#else

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstdint/uint16_t.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <hamon/cstdint/uint64_t.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <stdlib.h>

namespace hamon
{

namespace detail
{

inline HAMON_CXX11_CONSTEXPR hamon::uint16_t
byteswap_impl_uint16(hamon::uint16_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap16)
	return __builtin_bswap16(value);
#else
#if defined(HAMON_MSVC) && defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
	if (!hamon::is_constant_evaluated())
	{
		return _byteswap_ushort(value);
	}
#endif
	return static_cast<hamon::uint16_t>((value << 8) | (value >> 8));
#endif
}

inline HAMON_CXX11_CONSTEXPR hamon::uint32_t
byteswap_impl_uint32(hamon::uint32_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap32)
	return __builtin_bswap32(value);
#else
#if defined(HAMON_MSVC) && defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
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
byteswap_impl_uint64(hamon::uint64_t value) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_bswap64)
	return __builtin_bswap64(value);
#else
#if defined(HAMON_MSVC) && defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
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

template <typename T, hamon::size_t = sizeof(T)>
struct byteswap_impl;

template <typename T>
struct byteswap_impl<T, 1>
{
	static HAMON_CXX11_CONSTEXPR T invoke(T value) HAMON_NOEXCEPT
	{
		return value;
	}
};

template <typename T>
struct byteswap_impl<T, 2>
{
	static HAMON_CXX11_CONSTEXPR T invoke(T value) HAMON_NOEXCEPT
	{
		return static_cast<T>(byteswap_impl_uint16(static_cast<hamon::uint16_t>(value)));
	}
};

template <typename T>
struct byteswap_impl<T, 4>
{
	static HAMON_CXX11_CONSTEXPR T invoke(T value) HAMON_NOEXCEPT
	{
		return static_cast<T>(byteswap_impl_uint32(static_cast<hamon::uint32_t>(value)));
	}
};

template <typename T>
struct byteswap_impl<T, 8>
{
	static HAMON_CXX11_CONSTEXPR T invoke(T value) HAMON_NOEXCEPT
	{
		return static_cast<T>(byteswap_impl_uint64(static_cast<hamon::uint64_t>(value)));
	}
};

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
inline HAMON_CXX11_CONSTEXPR T
byteswap(T value) HAMON_NOEXCEPT
{
	return detail::byteswap_impl<T>::invoke(value);
}

}	// namespace hamon

#endif

#endif // HAMON_BIT_BYTESWAP_HPP
