/**
 *	@file	surface_density.hpp
 *
 *	@brief	surface_density の定義
 */

#ifndef HAMON_UNITS_SURFACE_DENSITY_HPP
#define HAMON_UNITS_SURFACE_DENSITY_HPP

#include <hamon/units/mass.hpp>
#include <hamon/units/area.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, Area) \
	template <typename T> using Mass ## _per_ ## Area = decltype(Mass<T>() / Area<T>())

#define HAMON_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, C, Length) \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## atto  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## femto ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## pico  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## nano  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## micro ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## milli ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## centi ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## deci  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## Length);            \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## deca  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## hecto ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## kilo  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## mega  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## giga  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## tera  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## peta  ## Length);   \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, C ## exa   ## Length)

#define HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(Mass)                      \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, square_, metre); \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX(Mass, square_, meter); \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_inch);              \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_foot);              \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_chain);             \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_furlong);           \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_yard);              \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, square_mile);              \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, are);                      \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, hectare);                  \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY(Mass, acre)

#define HAMON_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(Mass) \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(atto  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(femto ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(pico  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(nano  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(micro ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(milli ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(centi ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(deci  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(Mass);              \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(deca  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(hecto ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(kilo  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(mega  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(giga  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(tera  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(peta  ## Mass);     \
	HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(exa   ## Mass)

HAMON_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(gram);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX(grams);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(tonne);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(tonnes);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(pound);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(pounds);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(ounce);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(ounces);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(grain);
HAMON_UNITS_DECLARE_SURFACE_DENSITY_2(grains);

#undef HAMON_UNITS_DECLARE_SURFACE_DENSITY
#undef HAMON_UNITS_DECLARE_SURFACE_DENSITY_SI_PREFIX
#undef HAMON_UNITS_DECLARE_SURFACE_DENSITY_2
#undef HAMON_UNITS_DECLARE_SURFACE_DENSITY_2_SI_PREFIX

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SURFACE_DENSITY_HPP
