/**
 *	@file	signbit.hpp
 *
 *	@brief	signbit
 */

#ifndef HAMON_CMATH_SIGNBIT_HPP
#define HAMON_CMATH_SIGNBIT_HPP

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/ieee754/binary.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
signbit_impl_ct(FloatType x) HAMON_NOEXCEPT
{
	return hamon::ieee754::binary<FloatType>(x).sign();
}

template <typename FloatType>
HAMON_CXX11_CONSTEXPR bool
signbit_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_GCC) || (defined(HAMON_CLANG) && HAMON_CLANG >= 200000)
	// gcc または clang-20以上 なら __builtin_signbit は constexpr
	return __builtin_signbit(x);
#elif defined(HAMON_CLANG)
	return hamon::is_constant_evaluated() ? signbit_impl_ct(x) : __builtin_signbit(x);
#else
	return signbit_impl_ct(x);
#endif
}

}	// namespace detail

template <HAMON_CONSTRAINT(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool
signbit(Arithmetic x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::signbit_impl(static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_SIGNBIT_HPP
