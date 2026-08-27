/**
 *	@file	gcd.hpp
 *
 *	@brief	gcd の定義
 */

#ifndef HAMON_NUMERIC_GCD_HPP
#define HAMON_NUMERIC_GCD_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 26.10.14 Greatest common divisor[numeric.ops.gcd]

/**
 *	@brief		最大公約数を得る
 *
 *	@tparam		M	整数型
 *	@tparam		N	整数型
 *
 *	@param		m	整数値
 *	@param		n	整数値
 *
 *	@return		m と n の両方が 0 の場合、 0 を返す。
 *				そうでない場合、 |m| と |n| の最大公約数を返す。
 */
template <
	HAMON_CONSTRAINT(hamon::integral, M),
	HAMON_CONSTRAINT(hamon::integral, N)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<M, N> gcd(M m, N n) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [numeric.ops.gcd]/1
	static_assert(!hamon::is_same_v<hamon::remove_cv_t<M>, bool>, "");
	static_assert(!hamon::is_same_v<hamon::remove_cv_t<N>, bool>, "");

	return
		m == 0 ? hamon::abs(n) :
		n == 0 ? hamon::abs(m) :
		hamon::gcd(n, m % n);
}

}	// namespace hamon

#endif // HAMON_NUMERIC_GCD_HPP
