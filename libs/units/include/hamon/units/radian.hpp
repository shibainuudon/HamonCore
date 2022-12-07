/**
 *	@file	radian.hpp
 *
 *	@brief	radian の定義
 */

#ifndef HAMON_UNITS_RADIAN_HPP
#define HAMON_UNITS_RADIAN_HPP

#include <hamon/units/base_dimensions/angle.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/cmath/ranges/sin.hpp>
#include <hamon/cmath/ranges/cos.hpp>
#include <hamon/cmath/ranges/tan.hpp>

namespace hamon
{

namespace units
{

// ラジアン
template <typename T> using radian  = quantity<T, angle_dimension>;
template <typename T> using radians = radian<T>;

/**
 *	@brief	sinのオーバーロード
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
sin(radians<T> const& r) HAMON_NOEXCEPT
{
	return hamon::ranges::sin(r.value());
}

/**
 *	@brief	cosのオーバーロード
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
cos(radians<T> const& r) HAMON_NOEXCEPT
{
	return hamon::ranges::cos(r.value());
}

/**
 *	@brief	tanのオーバーロード
 */
template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T
tan(radians<T> const& r) HAMON_NOEXCEPT
{
	return hamon::ranges::tan(r.value());
}

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_RADIAN_HPP
