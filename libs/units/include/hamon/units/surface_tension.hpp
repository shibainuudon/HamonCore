/**
 *	@file	surface_tension.hpp
 *
 *	@brief	surface_tension の定義
 */

#ifndef HAMON_UNITS_SURFACE_TENSION_HPP
#define HAMON_UNITS_SURFACE_TENSION_HPP

#include <hamon/units/newton.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ニュートン毎メートル(表面張力の単位)
template <typename T> using newton_per_metre  = decltype(newton<T>() / metre<T>());
template <typename T> using newton_per_meter  = newton_per_metre<T>;
template <typename T> using newtons_per_metre = newton_per_metre<T>;
template <typename T> using newtons_per_meter = newton_per_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SURFACE_TENSION_HPP
