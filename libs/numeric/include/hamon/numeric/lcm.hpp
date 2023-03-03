/**
 *	@file	lcm.hpp
 *
 *	@brief	lcm の定義
 */

#ifndef HAMON_NUMERIC_LCM_HPP
#define HAMON_NUMERIC_LCM_HPP

#include <numeric>

#if defined(__cpp_lib_gcd_lcm) && (__cpp_lib_gcd_lcm >= 201606)

namespace hamon
{

using std::lcm;

}	// namespace hamon

#else

#include <hamon/numeric/gcd.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/config.hpp>

namespace hamon
{

/**
 *	@brief		最小公倍数を得る
 *
 *	@tparam		M	整数型
 *	@tparam		N	整数型
 *
 *	@param		m	整数値
 *	@param		n	整数値
 *
 *	@return		m と n のどちらかが 0 の場合、 0 を返す。
 *				そうでない場合、 |m| と |n| の最小公倍数を返す。
 */
template <
	HAMON_CONSTRAINED_PARAM(hamon::integral, M),
	HAMON_CONSTRAINED_PARAM(hamon::integral, N)
>
HAMON_CONSTEXPR hamon::common_type_t<M, N>
lcm(M m, N n)
HAMON_NOEXCEPT
{
	return
		(m == 0 || n == 0) ?
			0 :
		(hamon::abs(m) / hamon::gcd(m, n)) * hamon::abs(n);
}

}	// namespace hamon

#endif

#endif // HAMON_NUMERIC_LCM_HPP
