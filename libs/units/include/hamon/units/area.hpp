/**
 *	@file	area.hpp
 *
 *	@brief	area の定義
 */

#ifndef HAMON_UNITS_AREA_HPP
#define HAMON_UNITS_AREA_HPP

#include <hamon/units/length.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_AREA(Name)	\
	template <typename T> using square_ ## Name = decltype(Name<T>() * Name<T>())

#define HAMON_UNITS_DECLARE_AREA_SI_PREFIX(Name) \
	HAMON_UNITS_DECLARE_AREA(atto  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(femto ## Name);     \
	HAMON_UNITS_DECLARE_AREA(pico  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(nano  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(micro ## Name);     \
	HAMON_UNITS_DECLARE_AREA(milli ## Name);     \
	HAMON_UNITS_DECLARE_AREA(centi ## Name);     \
	HAMON_UNITS_DECLARE_AREA(deci  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(Name);              \
	HAMON_UNITS_DECLARE_AREA(deca  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(hecto ## Name);     \
	HAMON_UNITS_DECLARE_AREA(kilo  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(mega  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(giga  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(tera  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(peta  ## Name);     \
	HAMON_UNITS_DECLARE_AREA(exa   ## Name)

// 平方メートル
HAMON_UNITS_DECLARE_AREA_SI_PREFIX(metre);
HAMON_UNITS_DECLARE_AREA_SI_PREFIX(metres);
HAMON_UNITS_DECLARE_AREA_SI_PREFIX(meter);
HAMON_UNITS_DECLARE_AREA_SI_PREFIX(meters);

// 平方インチ (正確に 645.16 平方ミリメートル)
HAMON_UNITS_DECLARE_AREA(inch);
HAMON_UNITS_DECLARE_AREA(inches);

// 平方フィート (144平方インチ = 正確に 929.0304 平方センチメートル)
HAMON_UNITS_DECLARE_AREA(foot);
HAMON_UNITS_DECLARE_AREA(feet);

// 平方ヤード (9 平方フィート = 正確に 0.83612736 平方メートル)
HAMON_UNITS_DECLARE_AREA(yard);
HAMON_UNITS_DECLARE_AREA(yards);

// 平方チェーン
HAMON_UNITS_DECLARE_AREA(chain);
HAMON_UNITS_DECLARE_AREA(chains);

// 平方ハロン
HAMON_UNITS_DECLARE_AREA(furlong);
HAMON_UNITS_DECLARE_AREA(furlongs);

// 平方マイル (27878400 平方フィート = 正確に 2.5899881103 平方キロメートル)
HAMON_UNITS_DECLARE_AREA(mile);
HAMON_UNITS_DECLARE_AREA(miles);

#undef HAMON_UNITS_DECLARE_AREA
#undef HAMON_UNITS_DECLARE_AREA_SI_PREFIX

}	// namespace units

}	// namespace hamon

#include <hamon/units/acre.hpp>
#include <hamon/units/are.hpp>
#include <hamon/units/hectare.hpp>

#endif // HAMON_UNITS_AREA_HPP
