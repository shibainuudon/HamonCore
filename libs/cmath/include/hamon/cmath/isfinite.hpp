/**
 *	@file	isfinite.hpp
 *
 *	@brief	isfinite 関数の定義
 */

#ifndef HAMON_CMATH_ISFINITE_HPP
#define HAMON_CMATH_ISFINITE_HPP

#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename FloatType>
inline HAMON_CXX11_CONSTEXPR bool
isfinite_impl(FloatType x) HAMON_NOEXCEPT
{
#if defined(HAMON_USE_BUILTIN_CMATH_FUNCTION)
	return __builtin_isfinite(x);
#else
	return !hamon::isinf(x) && !hamon::isnan(x);
#endif
}

}	// namespace detail

/**
 *	@brief	有限の値かどうか調べる
 *
 *	@param	arg	調べる値
 *
 *	@return	argが有限の値ならtrue,∞またはNaNならfalse.
 *
 *	@note	argが整数型のときはdoubleにキャストしてから調べる。
 */
template <HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic)>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR bool
isfinite(Arithmetic arg) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic>;
	return detail::isfinite_impl(static_cast<type>(arg));
}

}	// namespace hamon

#endif // HAMON_CMATH_ISFINITE_HPP
