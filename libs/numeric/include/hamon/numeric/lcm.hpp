/**
 *	@file	lcm.hpp
 *
 *	@brief	lcm の定義
 */

#ifndef HAMON_NUMERIC_LCM_HPP
#define HAMON_NUMERIC_LCM_HPP

#include <hamon/numeric/gcd.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 26.10.15 Least common multiple[numeric.ops.lcm]

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
	HAMON_CONSTRAINT(hamon::integral, M),
	HAMON_CONSTRAINT(hamon::integral, N)
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::common_type_t<M, N> lcm(M m, N n) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [numeric.ops.lcm]/1
	static_assert(!hamon::is_same_v<hamon::remove_cv_t<M>, bool>, "");
	static_assert(!hamon::is_same_v<hamon::remove_cv_t<N>, bool>, "");

	return
		(m == 0 || n == 0) ?
			0 :
		(hamon::abs(m) / hamon::gcd(m, n)) * hamon::abs(n);
}

}	// namespace hamon

#endif // HAMON_NUMERIC_LCM_HPP
