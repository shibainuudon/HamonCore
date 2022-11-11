/**
 *	@file	angular_momentum.hpp
 *
 *	@brief	angular_momentum の定義
 */

#ifndef HAMON_UNITS_ANGULAR_MOMENTUM_HPP
#define HAMON_UNITS_ANGULAR_MOMENTUM_HPP

#include <hamon/units/newton.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ニュートンメートル秒(角運動量の単位)
template <typename T> using newton_metre_second  = decltype(newton<T>() * metre<T>() * second<T>());
template <typename T> using newton_metre_seconds = newton_metre_second<T>;
template <typename T> using newton_meter_second  = newton_metre_second<T>;
template <typename T> using newton_meter_seconds = newton_metre_second<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ANGULAR_MOMENTUM_HPP
