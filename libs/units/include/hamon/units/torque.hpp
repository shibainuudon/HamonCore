﻿/**
 *	@file	torque.hpp
 *
 *	@brief	torque の定義
 */

#ifndef HAMON_UNITS_TORQUE_HPP
#define HAMON_UNITS_TORQUE_HPP

#include <hamon/units/newton.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ニュートンメートル(力のモーメント（トルク）の単位)
template <typename T> using newton_metre  = decltype(newton<T>() * metre<T>());
template <typename T> using newton_metres = newton_metre<T>;
template <typename T> using newton_meter  = newton_metre<T>;
template <typename T> using newton_meters = newton_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_TORQUE_HPP
