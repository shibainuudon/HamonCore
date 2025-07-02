/**
 *	@file	ratio.hpp
 *
 *	@brief	ratio の定義
 */

#ifndef HAMON_RATIO_RATIO_HPP
#define HAMON_RATIO_RATIO_HPP

#include <hamon/ratio/config.hpp>

#if defined(HAMON_USE_STD_RATIO)

#include <ratio>

namespace hamon
{

using std::ratio;

}	// namespace hamon

#else

#include <hamon/cstdint/intmax_t.hpp>
#include <hamon/numeric/gcd.hpp>

namespace hamon
{

namespace detail
{

inline constexpr hamon::intmax_t abs(hamon::intmax_t x) noexcept
{
	return x < 0 ? -x : x;
}

inline constexpr hamon::intmax_t sgn(hamon::intmax_t x) noexcept
{
	return x < 0 ? -1 : 1;
}

}	// namespace detail

// 21.4.3 Class template ratio[ratio.ratio]

template <hamon::intmax_t N, hamon::intmax_t D = 1>
class ratio
{
	// [ratio.ratio]/1
	static_assert(D != 0, "");
public:
	static constexpr hamon::intmax_t num = hamon::detail::sgn(N) * hamon::detail::sgn(D) * hamon::detail::abs(N) / hamon::gcd(N, D);
	static constexpr hamon::intmax_t den = hamon::detail::abs(D) / hamon::gcd(N, D);
	using type = hamon::ratio<num, den>;
};

}	// namespace hamon

#endif

#endif // HAMON_RATIO_RATIO_HPP
