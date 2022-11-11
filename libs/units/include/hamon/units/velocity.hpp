/**
 *	@file	velocity.hpp
 *
 *	@brief	velocity の定義
 */

#ifndef HAMON_UNITS_VELOCITY_HPP
#define HAMON_UNITS_VELOCITY_HPP

#include <hamon/units/length.hpp>
#include <hamon/units/time.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_VELOCITY_1(Length, Time)	\
	template <typename T> using Length ## _per_ ## Time = decltype(Length<T>() / Time<T>())

#define HAMON_UNITS_DECLARE_VELOCITY(Length)	\
	HAMON_UNITS_DECLARE_VELOCITY_1(Length, second);	\
	HAMON_UNITS_DECLARE_VELOCITY_1(Length, minute);	\
	HAMON_UNITS_DECLARE_VELOCITY_1(Length, hour)

#define HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX(Length) \
	HAMON_UNITS_DECLARE_VELOCITY(atto  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(femto ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(pico  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(nano  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(micro ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(milli ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(centi ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(deci  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(Length);              \
	HAMON_UNITS_DECLARE_VELOCITY(deca  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(hecto ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(kilo  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(mega  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(giga  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(tera  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(peta  ## Length);     \
	HAMON_UNITS_DECLARE_VELOCITY(exa   ## Length)

HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX(metre);
HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX(metres);
HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX(meter);
HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX(meters);
HAMON_UNITS_DECLARE_VELOCITY(inch);
HAMON_UNITS_DECLARE_VELOCITY(inches);
HAMON_UNITS_DECLARE_VELOCITY(foot);
HAMON_UNITS_DECLARE_VELOCITY(feet);
HAMON_UNITS_DECLARE_VELOCITY(yard);
HAMON_UNITS_DECLARE_VELOCITY(yards);
HAMON_UNITS_DECLARE_VELOCITY(chain);
HAMON_UNITS_DECLARE_VELOCITY(chains);
HAMON_UNITS_DECLARE_VELOCITY(furlong);
HAMON_UNITS_DECLARE_VELOCITY(furlongs);
HAMON_UNITS_DECLARE_VELOCITY(mile);
HAMON_UNITS_DECLARE_VELOCITY(miles);

#undef HAMON_UNITS_DECLARE_VELOCITY_1
#undef HAMON_UNITS_DECLARE_VELOCITY
#undef HAMON_UNITS_DECLARE_VELOCITY_SI_PREFIX

}	// namespace units

}	// namespace hamon

#include <hamon/units/knot.hpp>

#endif // HAMON_UNITS_VELOCITY_HPP
