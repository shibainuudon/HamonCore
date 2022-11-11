/**
 *	@file	volume.hpp
 *
 *	@brief	volume の定義
 */

#ifndef HAMON_UNITS_VOLUME_HPP
#define HAMON_UNITS_VOLUME_HPP

#include <hamon/units/length.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_VOLUME(Name)	\
	template <typename T> using cubic_ ## Name = decltype(Name<T>() * Name<T>() * Name<T>())

#define HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX(Name) \
	HAMON_UNITS_DECLARE_VOLUME(atto  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(femto ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(pico  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(nano  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(micro ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(milli ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(centi ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(deci  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(Name);              \
	HAMON_UNITS_DECLARE_VOLUME(deca  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(hecto ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(kilo  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(mega  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(giga  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(tera  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(peta  ## Name);     \
	HAMON_UNITS_DECLARE_VOLUME(exa   ## Name)

// 立方メートル
HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX(metre);
HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX(metres);
HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX(meter);
HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX(meters);

// 立方インチ
HAMON_UNITS_DECLARE_VOLUME(inch);
HAMON_UNITS_DECLARE_VOLUME(inches);

// 立方フィート
HAMON_UNITS_DECLARE_VOLUME(foot);
HAMON_UNITS_DECLARE_VOLUME(feet);

// 立方ヤード
HAMON_UNITS_DECLARE_VOLUME(yard);
HAMON_UNITS_DECLARE_VOLUME(yards);

// 立方チェーン
HAMON_UNITS_DECLARE_VOLUME(chain);
HAMON_UNITS_DECLARE_VOLUME(chains);

// 立方ハロン
HAMON_UNITS_DECLARE_VOLUME(furlong);
HAMON_UNITS_DECLARE_VOLUME(furlongs);

// 立方マイル
HAMON_UNITS_DECLARE_VOLUME(mile);
HAMON_UNITS_DECLARE_VOLUME(miles);

#undef HAMON_UNITS_DECLARE_VOLUME
#undef HAMON_UNITS_DECLARE_VOLUME_SI_PREFIX

}	// namespace units

}	// namespace hamon

#include <hamon/units/litre.hpp>

#endif // HAMON_UNITS_VOLUME_HPP
