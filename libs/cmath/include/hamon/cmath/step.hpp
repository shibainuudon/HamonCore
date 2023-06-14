/**
 *	@file	step.hpp
 *
 *	@brief	step 関数の定義
 */

#ifndef HAMON_CMATH_STEP_HPP
#define HAMON_CMATH_STEP_HPP

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
inline HAMON_CXX11_CONSTEXPR FloatType
step_impl(FloatType a, FloatType x) HAMON_NOEXCEPT
{
	return
		hamon::isnan(a) || hamon::isnan(x) ?
			FloatType(0) :
		x >= a ?
			FloatType(1) :
		FloatType(0);
}

}	// namespace detail

/**
 *	@brief	step
 *
 *	@tparam		Arithmetic1	算術型
 *	@tparam		Arithmetic2	算術型
 *
 *	@param	a
 *	@param	x
 *
 *	@return	x < a の場合は0。x >= a の場合は1。
 *
 *	a と x の少なくともどちらかが NaN の場合、0 を返す。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic1),
	HAMON_CONSTRAINED_PARAM(hamon::arithmetic, Arithmetic2)
>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR hamon::float_promote_t<Arithmetic1, Arithmetic2>
step(Arithmetic1 a, Arithmetic2 x) HAMON_NOEXCEPT
{
	using type = hamon::float_promote_t<Arithmetic1, Arithmetic2>;
	return detail::step_impl(static_cast<type>(a), static_cast<type>(x));
}

}	// namespace hamon

#endif // HAMON_CMATH_STEP_HPP
