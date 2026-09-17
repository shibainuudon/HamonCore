/**
 *	@file	memmove.hpp
 *
 *	@brief	memmove 関数を定義
 */

#ifndef HAMON_CSTRING_MEMMOVE_HPP
#define HAMON_CSTRING_MEMMOVE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>
#include <cstring>

namespace hamon
{

namespace detail
{

// (1) T == U で is_trivially_copyable_v<T> な場合
template <typename T, typename = hamon::enable_if_t<hamon::is_trivially_copyable_v<T>>>
HAMON_CXX14_CONSTEXPR
T* memmove_impl(T* s1, T const* s2, hamon::size_t n, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
{
	HAMON_ASSERT((n % sizeof(T)) == 0u);
	n /= sizeof(T);

	if (s2 < s1 && s1 < s2 + n)
	{
		// copy backward
		for (hamon::size_t i = n; i != 0; --i)
		{
			s1[i - 1] = s2[i - 1];
		}
	}
	else
	{
		// copy forward
		for (hamon::size_t i = 0; i != n; ++i)
		{
			s1[i] = s2[i];
		}
	}

	return s1;
}

// (2) 上記のいずれでもない場合、constexprにはできない
template <typename T, typename U>
T* memmove_impl(T* s1, U const* s2, hamon::size_t n, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT
{
	return static_cast<T*>(std::memmove(s1, s2, n));
}

}	// namespace detail

/**
 *	@brief	メモリ領域の移動
 *
 *	この関数は以下の条件を全て満たす場合、constexpr関数として評価される
 *	・sizeof(T) == sizeof(U)であること
 *	・is_trivially_copyable_v<T> == trueであること
 *	・is_trivially_copyable_v<U> == trueであること
 *	・s1とs2が同じ配列の要素を指している
 */
template <typename T, typename U>
HAMON_CXX14_CONSTEXPR
T* memmove(T* s1, U const* s2, hamon::size_t n) HAMON_NOEXCEPT
{
	if (!hamon::is_constant_evaluated())
	{
		return static_cast<T*>(std::memmove(s1, s2, n));
	}

	return hamon::detail::memmove_impl(s1, s2, n, hamon::detail::overload_priority<1>{});
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMMOVE_HPP
