/**
 *	@file	angular_velocity.hpp
 *
 *	@brief	angular_velocity の定義
 */

#ifndef HAMON_UNITS_ANGULAR_VELOCITY_HPP
#define HAMON_UNITS_ANGULAR_VELOCITY_HPP

#include <hamon/units/radian.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ラジアン毎秒(角速度の単位)
template <typename T> using radian_per_second  = decltype(radian<T>() / second<T>());
template <typename T> using radians_per_second = radian_per_second<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ANGULAR_VELOCITY_HPP
