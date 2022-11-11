/**
 *	@file	mass_density.hpp
 *
 *	@brief	mass_density の定義
 */

#ifndef HAMON_UNITS_MASS_DENSITY_HPP
#define HAMON_UNITS_MASS_DENSITY_HPP

#include <hamon/units/mass.hpp>
#include <hamon/units/volume.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, Volume) \
	template <typename T> using Mass ## _per_ ## Volume = decltype(Mass<T>() / Volume<T>())

#define HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, C, Length) \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## atto  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## femto ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## pico  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## nano  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## micro ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## milli ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## centi ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## deci  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## Length);            \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## deca  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## hecto ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## kilo  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## mega  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## giga  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## tera  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## peta  ## Length);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, C ## exa   ## Length)

#define HAMON_UNITS_DECLARE_MASS_DENSITY_2(Mass)                     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, cubic_, metre); \
	HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, cubic_, meter); \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_inch);              \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_foot);              \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_chain);             \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_furlong);           \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_yard);              \
	HAMON_UNITS_DECLARE_MASS_DENSITY(Mass, cubic_mile);              \
	HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, /**/, litre);   \
	HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX(Mass, /**/, liter)

#define HAMON_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(Mass) \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(atto  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(femto ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(pico  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(nano  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(micro ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(milli ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(centi ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(deci  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(Mass);              \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(deca  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(hecto ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(kilo  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(mega  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(giga  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(tera  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(peta  ## Mass);     \
	HAMON_UNITS_DECLARE_MASS_DENSITY_2(exa   ## Mass)

HAMON_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(gram);
HAMON_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX(grams);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(tonne);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(tonnes);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(pound);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(pounds);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(ounce);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(ounces);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(grain);
HAMON_UNITS_DECLARE_MASS_DENSITY_2(grains);

#undef HAMON_UNITS_DECLARE_MASS_DENSITY
#undef HAMON_UNITS_DECLARE_MASS_DENSITY_SI_PREFIX
#undef HAMON_UNITS_DECLARE_MASS_DENSITY_2
#undef HAMON_UNITS_DECLARE_MASS_DENSITY_2_SI_PREFIX

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MASS_DENSITY_HPP
