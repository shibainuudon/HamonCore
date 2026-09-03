/**
 *	@file	popcount_impl.hpp
 *
 *	@brief	popcount_impl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_DETAIL_POPCOUNT_IMPL_HPP
#define HAMON_BIT_DETAIL_POPCOUNT_IMPL_HPP

#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// UINT8_C, UINT16_C, UINT32_C, UINT64_C

#if defined(HAMON_MSVC)
#include <intrin.h>	// __popcnt16, __popcnt, __popcnt64
#endif

namespace hamon
{
namespace detail
{

// アルゴリズムに関する詳細は
// https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel
// を参照してください。

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 1>>
HAMON_CXX14_CONSTEXPR int
popcount_fallback_impl(T x, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT8_C(0x55)));
	x = ((x & UINT8_C(0x33)) + ((x >> 2) & UINT8_C(0x33)));
	x = ((x + (x >> 4)) & UINT8_C(0x0f));
	x = (x * UINT8_C(0x01));
	return static_cast<int>(x);
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 2>>
HAMON_CXX14_CONSTEXPR int
popcount_fallback_impl(T x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT16_C(0x5555)));
	x = ((x & UINT16_C(0x3333)) + ((x >> 2) & UINT16_C(0x3333)));
	x = ((x + (x >> 4)) & UINT16_C(0x0f0f));
	x = (x * UINT16_C(0x0101));
	return static_cast<int>(x >> 8);
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 4>>
HAMON_CXX14_CONSTEXPR int
popcount_fallback_impl(T x, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT32_C(0x55555555)));
	x = ((x & UINT32_C(0x33333333)) + ((x >> 2) & UINT32_C(0x33333333)));
	x = ((x + (x >> 4)) & UINT32_C(0x0f0f0f0f));
	x = (x * UINT32_C(0x01010101));
	return static_cast<int>(x >> 24);
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 8>>
HAMON_CXX14_CONSTEXPR int
popcount_fallback_impl(T x, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
{
	x = (x - ((x >> 1) & UINT64_C(0x5555555555555555)));
	x = ((x & UINT64_C(0x3333333333333333)) + ((x >> 2) & UINT64_C(0x3333333333333333)));
	x = ((x + (x >> 4)) & UINT64_C(0x0f0f0f0f0f0f0f0f));
	x = (x * UINT64_C(0x0101010101010101));
	return static_cast<int>(x >> 56);
}

template <typename T>
HAMON_CXX14_CONSTEXPR int
popcount_fallback(T x) HAMON_NOEXCEPT
{
	return popcount_fallback_impl(x, hamon::detail::overload_priority<3>{});
}

#if defined(HAMON_MSVC)

template <typename T, typename = hamon::enable_if_t<sizeof(T) <= 2>>
HAMON_CXX14_CONSTEXPR int
popcount_msvc_impl(T x, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return static_cast<int>(__popcnt16(x));
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 4>>
HAMON_CXX14_CONSTEXPR int
popcount_msvc_impl(T x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	return static_cast<int>(__popcnt(x));
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 8>>
HAMON_CXX14_CONSTEXPR int
popcount_msvc_impl(T x, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
#ifdef _WIN64
	return static_cast<int>(__popcnt64(x));
#else
	return static_cast<int>(__popcnt(x >> 32) + __popcnt(static_cast<unsigned int>(x)));
#endif
}

template <typename T>
HAMON_CXX14_CONSTEXPR int
popcount_msvc(T x) HAMON_NOEXCEPT
{
	if (hamon::is_constant_evaluated())
	{
		return popcount_fallback(x);
	}
	return popcount_msvc_impl(x, hamon::detail::overload_priority<2>{});
}

#endif

template <typename T>
HAMON_CXX14_CONSTEXPR int
popcount_impl(T x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_popcountg)
	return __builtin_popcountg(x);
#elif defined(HAMON_MSVC)
	return popcount_msvc(x);
#else
	return popcount_fallback(x);
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIT_DETAIL_POPCOUNT_IMPL_HPP
