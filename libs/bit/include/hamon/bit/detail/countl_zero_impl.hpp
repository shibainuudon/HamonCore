/**
 *	@file	countl_zero_impl.hpp
 *
 *	@brief	countl_zero_impl 関数テンプレートを定義
 */

#ifndef HAMON_BIT_DETAIL_COUNTL_ZERO_IMPL_HPP
#define HAMON_BIT_DETAIL_COUNTL_ZERO_IMPL_HPP

#include <hamon/bit/popcount.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/limits.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_MSVC)
#include <intrin.h>	// _BitScanReverse, _BitScanReverse64
#endif

namespace hamon
{
namespace detail
{

// アルゴリズムに関する詳細は
// Hacker's Delight (ハッカーのたのしみ) ヘンリー・S・ウォーレン、ジュニア著
// http://www.hackersdelight.org/
// を参照してください。

// countl_zero_fallback
template <typename T, typename = hamon::enable_if_t<sizeof(T) == 1>>
HAMON_CXX14_CONSTEXPR int
countl_zero_fallback_impl(T x, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	x = (x | (x >> 1));
	x = (x | (x >> 2));
	x = (x | (x >> 4));
	return popcount(static_cast<T>(~x));
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 2>>
HAMON_CXX14_CONSTEXPR int
countl_zero_fallback_impl(T x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	x = (x | (x >> 1));
	x = (x | (x >> 2));
	x = (x | (x >> 4));
	x = (x | (x >> 8));
	return popcount(static_cast<T>(~x));
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 4>>
HAMON_CXX14_CONSTEXPR int
countl_zero_fallback_impl(T x, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	x = (x | (x >> 1));
	x = (x | (x >> 2));
	x = (x | (x >> 4));
	x = (x | (x >> 8));
	x = (x | (x >> 16));
	return popcount(static_cast<T>(~x));
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 8>>
HAMON_CXX14_CONSTEXPR int
countl_zero_fallback_impl(T x, hamon::detail::overload_priority<3>) HAMON_NOEXCEPT
{
	x = (x | (x >> 1));
	x = (x | (x >> 2));
	x = (x | (x >> 4));
	x = (x | (x >> 8));
	x = (x | (x >> 16));
	x = (x | (x >> 32));
	return popcount(static_cast<T>(~x));
}

template <typename T>
HAMON_CXX14_CONSTEXPR int
countl_zero_fallback(T x) HAMON_NOEXCEPT
{
	return countl_zero_fallback_impl(x, hamon::detail::overload_priority<3>{});
}

// countl_zero_msvc
#if defined(HAMON_MSVC)

template <typename T, typename = hamon::enable_if_t<sizeof(T) <= 4>>
HAMON_CXX14_CONSTEXPR int
countl_zero_msvc_impl(T x, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	const int N = hamon::numeric_limits<T>::digits;
	unsigned long result;
	if (!_BitScanReverse(&result, x))
	{
		return N;
	}
	return static_cast<int>(N - 1 - result);
}

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 8>>
HAMON_CXX14_CONSTEXPR int
countl_zero_msvc_impl(T x, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	const int N = hamon::numeric_limits<T>::digits;
	unsigned long result;
#ifdef _WIN64
	if (!_BitScanReverse64(&result, x))
	{
		return N;
	}
#else
	if (_BitScanReverse(&result, static_cast<unsigned long>(x >> 32)))
	{
		return static_cast<int>(31 - result);
	}
	if (!_BitScanReverse(&result, static_cast<unsigned long>(x)))
	{
		return N;
	}
#endif
	return static_cast<int>(N - 1 - result);
}

template <typename T>
HAMON_CXX14_CONSTEXPR int
countl_zero_msvc(T x) HAMON_NOEXCEPT
{
	if (hamon::is_constant_evaluated())
	{
		return countl_zero_fallback(x);
	}
	return countl_zero_msvc_impl(x, hamon::detail::overload_priority<1>{});
}

#endif

// countl_zero_impl
template <typename T>
HAMON_CXX14_CONSTEXPR int
countl_zero_impl(T x) HAMON_NOEXCEPT
{
#if HAMON_HAS_BUILTIN(__builtin_clzg)
	return __builtin_clzg(x, hamon::numeric_limits<T>::digits);
#elif defined(HAMON_MSVC)
	return countl_zero_msvc(x);
#else
	return countl_zero_fallback(x);
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_BIT_DETAIL_COUNTL_ZERO_IMPL_HPP
