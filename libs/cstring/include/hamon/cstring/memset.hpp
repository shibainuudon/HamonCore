/**
 *	@file	memset.hpp
 *
 *	@brief	memset 関数を定義
 */

#ifndef HAMON_CSTRING_MEMSET_HPP
#define HAMON_CSTRING_MEMSET_HPP

#include <hamon/bit/bit_cast.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <cstring>

namespace hamon
{

namespace detail
{

// (1) is_trivially_copyable_v<T> な場合
template <typename T, typename = hamon::enable_if_t<hamon::is_trivially_copyable_v<T>>>
HAMON_CXX14_CONSTEXPR
T* memset_impl(T* s, unsigned char c, hamon::size_t n, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	constexpr hamon::size_t N = sizeof(T);

	// 配列をcで埋めて、コピー用の値を作る
	unsigned char a[N]{};
	for (hamon::size_t i = 0; i < N; ++i)
	{
		a[i] = c;
	}
	T const value = hamon::bit_cast<T>(a);

	auto ret = s;
	for (hamon::size_t i = 0; i < n; i += N)
	{
		*s++ = value;
	}
	return ret;
}

// (2) 上記のいずれでもない場合、constexprにはできない
template <typename T>
HAMON_CXX14_CONSTEXPR
T* memset_impl(T* s, unsigned char c, hamon::size_t n, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return static_cast<T*>(std::memset(s, c, n));
}

}	// namespace detail

/**
 *	@brief	memset
 *
 *	この関数は以下の条件を全て満たす場合、constexpr関数として評価される
 *	・is_trivially_copyable_v<T> == trueであること
 */
template <typename T>
HAMON_CXX14_CONSTEXPR
T* memset(T* s, int c, hamon::size_t n) HAMON_NOEXCEPT
{
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<T*>(std::memset(s, c, n));
	}

	return hamon::detail::memset_impl(s, static_cast<unsigned char>(c), n, hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMSET_HPP
