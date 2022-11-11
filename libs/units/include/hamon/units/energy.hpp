/**
 *	@file	energy.hpp
 *
 *	@brief	energy の定義
 */

#ifndef HAMON_UNITS_ENERGY_HPP
#define HAMON_UNITS_ENERGY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/erg.hpp>
#include <hamon/units/foot_poundal.hpp>
#include <hamon/units/calorie.hpp>
#include <hamon/units/watt.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/minute.hpp>
#include <hamon/units/hour.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ワット秒、キロワット時
#define HAMON_UNITS_DECLARE_ENERGY_1(Name, Time) \
	template <typename T> using Name ## _ ## Time = decltype(Name<T>() * Time<T>());	\
	HAMON_UNITS_SI_PREFIX(Name ## _ ## Time)

#define HAMON_UNITS_DECLARE_ENERGY_2(Name)      \
	HAMON_UNITS_DECLARE_ENERGY_1(Name, second);	\
	HAMON_UNITS_DECLARE_ENERGY_1(Name, minute);	\
	HAMON_UNITS_DECLARE_ENERGY_1(Name, hour)

HAMON_UNITS_DECLARE_ENERGY_2(watt);
HAMON_UNITS_DECLARE_ENERGY_2(watts);

#undef HAMON_UNITS_DECLARE_ENERGY_1
#undef HAMON_UNITS_DECLARE_ENERGY_2

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ENERGY_HPP
