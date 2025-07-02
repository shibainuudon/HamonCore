/**
 *	@file	ratio_multiply.hpp
 *
 *	@brief	ratio_multiply の定義
 */

#ifndef HAMON_RATIO_RATIO_MULTIPLY_HPP
#define HAMON_RATIO_RATIO_MULTIPLY_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio_multiply;

}	// namespace hamon

#else

#include <hamon/ratio/ratio.hpp>
#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/numeric/gcd.hpp>

namespace hamon
{

// 21.4.4 Arithmetic on ratios[ratio.arithmetic]

namespace detail
{

template <typename R1, typename R2>
struct ratio_multiply_impl
{
private:
	static constexpr hamon::intmax_t gcd_n1_d2 = hamon::gcd(R1::num, R2::den);
	static constexpr hamon::intmax_t gcd_d1_n2 = hamon::gcd(R1::den, R2::num);

public:
	using type = typename hamon::ratio<
		(R1::num / gcd_n1_d2) * (R2::num / gcd_d1_n2),
		(R2::den / gcd_n1_d2) * (R1::den / gcd_d1_n2)>::type;
};

}	// namespace detail

template <typename R1, typename R2>
using ratio_multiply = typename hamon::detail::ratio_multiply_impl<R1, R2>::type;

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_MULTIPLY_HPP
