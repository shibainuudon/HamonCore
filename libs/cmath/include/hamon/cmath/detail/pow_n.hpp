/**
 *	@file	pow_n.hpp
 *
 *	@brief	pow_n 関数の定義
 */

#ifndef HAMON_CMATH_DETAIL_POW_N_HPP
#define HAMON_CMATH_DETAIL_POW_N_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
inline HAMON_CONSTEXPR T
pow2(T const& x) HAMON_NOEXCEPT
{
	return x * x;
}

template <typename T>
inline HAMON_CONSTEXPR T
pow3(T const& x) HAMON_NOEXCEPT
{
	return x * x * x;
}

template <typename T>
inline HAMON_CONSTEXPR T
pow4(T const& x) HAMON_NOEXCEPT
{
	return x * x * x * x;
}

template <typename T>
inline HAMON_CONSTEXPR T
pow5(T const& x) HAMON_NOEXCEPT
{
	return x * x * x * x * x;
}

template <typename T, typename IntType>
inline HAMON_CONSTEXPR T
pow_n_impl(T const& x, IntType n) HAMON_NOEXCEPT
{
	return
		n == 1 ?
			x :
		n % 2 ?
			x * pow2(pow_n_impl(x, n / 2)) :
			pow2(pow_n_impl(x, n / 2));
}

template <
	typename T, typename UIntType,
	hamon::enable_if_t<std::is_unsigned<UIntType>::value>* = nullptr
>
inline HAMON_CONSTEXPR T
pow_n(T const& x, UIntType n) HAMON_NOEXCEPT
{
	return
		n == 0 ?
			T(1) :
			pow_n_impl(x, n);
}

template <
	typename T, typename IntType,
	hamon::enable_if_t<std::is_signed<IntType>::value>* = nullptr
>
inline HAMON_CONSTEXPR T
pow_n(T const& x, IntType n) HAMON_NOEXCEPT
{
	return
		n == 0 ?
			T(1) :
		n > 0 ?
			pow_n_impl(x, n) :
			T(1) / pow_n_impl(x, -n);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CMATH_DETAIL_POW_N_HPP
