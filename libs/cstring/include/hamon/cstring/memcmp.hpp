/**
 *	@file	memcmp.hpp
 *
 *	@brief	memcmp 関数を定義
 */

#ifndef HAMON_CSTRING_MEMCMP_HPP
#define HAMON_CSTRING_MEMCMP_HPP

#include <hamon/array.hpp>
#include <hamon/bit/bit_cast.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <cstring>

namespace hamon
{

namespace detail
{

#if defined(HAMON_MSVC) || defined(HAMON_CLANG)		// gccの__builtin_memcmpはconstexprにできない
template <typename T, typename = hamon::enable_if_t<sizeof(T) == 1 && !hamon::is_same_v<T, bool>>>
HAMON_CXX14_CONSTEXPR
int memcmp_impl(const T* s1, const T* s2, hamon::size_t n, hamon::detail::overload_priority<2>)
{
	return __builtin_memcmp(s1, s2, n);
}
#endif

template <typename T, typename = hamon::enable_if_t<sizeof(T) == 1>>
HAMON_CXX14_CONSTEXPR
int memcmp_impl(const T* s1, const T* s2, hamon::size_t n, hamon::detail::overload_priority<1>)
{
	for (hamon::size_t i = 0; i < n; ++i)
	{
		auto x = hamon::bit_cast<unsigned char>(*s1);
		auto y = hamon::bit_cast<unsigned char>(*s2);
		if (x < y)
		{
			return -1;
		}
		else if (x > y)
		{
			return 1;
		}

		++s1;
		++s2;
	}
	return 0;
}

template <typename T>
HAMON_CXX14_CONSTEXPR
int memcmp_impl(const T* s1, const T* s2, hamon::size_t n, hamon::detail::overload_priority<0>)
{
	// constexprにするため、unsigned charの配列にbit_castしてから比較する
	for (hamon::size_t i = 0; i < n; i += sizeof(T))
	{
		using Array = hamon::array<unsigned char, sizeof(T)>;
		auto x = hamon::bit_cast<Array>(*s1);
		auto y = hamon::bit_cast<Array>(*s2);
		if (x < y)
		{
			return -1;
		}
		else if (x > y)
		{
			return 1;
		}

		++s1;
		++s2;
	}
	return 0;
}

}	// namespace detail

template <typename T>
HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
int memcmp(const T* s1, const T* s2, hamon::size_t n)
{
	if (!hamon::is_constant_evaluated())
	{
		return std::memcmp(s1, s2, n);
	}

	return hamon::detail::memcmp_impl(s1, s2, n, hamon::detail::overload_priority<2>{});
}

}	// namespace hamon

#endif // HAMON_CSTRING_MEMCMP_HPP
