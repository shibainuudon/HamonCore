/**
 *	@file	ratio_gcd.hpp
 *
 *	@brief	ratio_gcdの定義
 */

#ifndef HAMON_RATIO_RATIO_GCD_HPP
#define HAMON_RATIO_RATIO_GCD_HPP

#include <hamon/ratio/ratio.hpp>
#include <hamon/numeric/gcd.hpp>
#include <hamon/numeric/lcm.hpp>

namespace hamon
{

/**
 *	@brief	ratio_gcd
 */
template <typename R1, typename R2>
using ratio_gcd = typename hamon::ratio<
	hamon::gcd(R1::num, R2::num),
	hamon::lcm(R1::den, R2::den)
>::type;

}	// namespace hamon

#endif // HAMON_RATIO_RATIO_GCD_HPP
