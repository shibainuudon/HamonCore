/**
 *	@file	angular_acceleration.hpp
 *
 *	@brief	angular_acceleration の定義
 */

#ifndef HAMON_UNITS_ANGULAR_ACCELERATION_HPP
#define HAMON_UNITS_ANGULAR_ACCELERATION_HPP

#include <hamon/units/radian.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ラジアン毎秒毎秒(角加速度の単位)
template <typename T> using radian_per_second_squared  = decltype(radian<T>() / second<T>() / second<T>());
template <typename T> using radians_per_second_squared = radian_per_second_squared<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ANGULAR_ACCELERATION_HPP
