/**
 *	@file	kinematic_viscosity.hpp
 *
 *	@brief	kinematic_viscosity の定義
 */

#ifndef HAMON_UNITS_KINEMATIC_VISCOSITY_HPP
#define HAMON_UNITS_KINEMATIC_VISCOSITY_HPP

#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// 平方メートル毎秒(動粘度の単位)
template <typename T> using square_metre_per_second  = decltype(metre<T>() * metre<T>() / second<T>());
template <typename T> using square_metres_per_second = square_metre_per_second<T>;
template <typename T> using square_meter_per_second  = square_metre_per_second<T>;
template <typename T> using square_meters_per_second = square_metre_per_second<T>;

}	// namespace units

}	// namespace hamon

#include <hamon/units/stokes.hpp>

#endif // HAMON_UNITS_KINEMATIC_VISCOSITY_HPP
