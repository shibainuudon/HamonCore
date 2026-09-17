/**
 *	@file	memcpy.hpp
 *
 *	@brief	memcpy 関数を定義
 */

#ifndef HAMON_CSTRING_MEMCPY_HPP
#define HAMON_CSTRING_MEMCPY_HPP

#include <hamon/bit/bit_cast.hpp>
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

// (1)
// T == U で is_trivially_copyable_v<T> な場合、
// 単純にループしながらコピーすれば良いのでconstexprにできる
template <typename T, typename = hamon::enable_if_t<hamon::is_trivially_copyable_v<T>>>
HAMON_CXX14_CONSTEXPR
T* memcpy_impl(T* s1, T const* s2, hamon::size_t n, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
{
	auto ret = s1;
	for (hamon::size_t i = 0; i < n; i += sizeof(T))
	{
		*s1++ = *s2++;
	}
	return ret;
}

// (2)
// UからTにbit_cast可能な場合、
// bit_castしながらコピーすれば良いのでconstexprにできる
template <typename T, typename U,
	typename = hamon::enable_if_t<
		sizeof(T) == sizeof(U) &&
		hamon::is_trivially_copyable_v<T> &&
		hamon::is_trivially_copyable_v<U>
	>
>
HAMON_CXX14_CONSTEXPR
T* memcpy_impl(T* s1, U const* s2, hamon::size_t n, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	auto ret = s1;
	for (hamon::size_t i = 0; i < n; i += sizeof(T))
	{
		*s1++ = hamon::bit_cast<T>(*s2++);
	}
	return ret;
}

// (3)
// 上記のいずれでもない場合、constexprにはできない
template <typename T, typename U>
T* memcpy_impl(T* s1, U const* s2, hamon::size_t n, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return static_cast<T*>(std::memcpy(s1, s2, n));
}

// TODO: C++26からはconstexpr関数内でvoid*からのキャストが可能になるので、
// 上記のどの場合でもconstexprにできるようになる。

}	// namespace detail

/**
 *	@brief	メモリ領域のコピー
 *
 *	この関数は以下の条件を全て満たす場合、constexpr関数として評価される
 *	・sizeof(T) == sizeof(U)であること
 *	・is_trivially_copyable_v<T> == trueであること
 *	・is_trivially_copyable_v<U> == trueであること
 */
template <typename T, typename U>
HAMON_CXX14_CONSTEXPR
T* memcpy(T* s1, U const* s2, hamon::size_t n) HAMON_NOEXCEPT
{
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<T*>(std::memcpy(s1, s2, n));
	}

	return hamon::detail::memcpy_impl(s1, s2, n, hamon::detail::overload_priority<2>{});
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMCPY_HPP
