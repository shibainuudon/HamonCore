/**
 *	@file	acceleration.hpp
 *
 *	@brief	acceleration の定義
 */

#ifndef HAMON_UNITS_ACCELERATION_HPP
#define HAMON_UNITS_ACCELERATION_HPP

#include <hamon/units/length.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/minute.hpp>
#include <hamon/units/hour.hpp>
#include <hamon/units/gal.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

#define HAMON_UNITS_DECLARE_ACCELERATION_1(Length, Time)	\
	template <typename T> using Length ## _per_ ## Time ## _squared = decltype(Length<T>() / Time<T>() / Time<T>())

#define HAMON_UNITS_DECLARE_ACCELERATION_2(Length, Time)	\
	HAMON_UNITS_DECLARE_ACCELERATION_1(Length, Time);	\
	HAMON_UNITS_SI_PREFIX(Length ## _per_ ## Time ## _squared)

#define HAMON_UNITS_DECLARE_ACCELERATION_3(F, Length)	\
	F(Length, second);	\
	F(Length, minute);	\
	F(Length, hour)

#define HAMON_UNITS_DECLARE_ACCELERATION(Length)	\
	HAMON_UNITS_DECLARE_ACCELERATION_3(HAMON_UNITS_DECLARE_ACCELERATION_1, Length)

#define HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX(Length) \
	HAMON_UNITS_DECLARE_ACCELERATION_3(HAMON_UNITS_DECLARE_ACCELERATION_2, Length)

// メートル毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX(metre);
HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX(metres);
HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX(meter);
HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX(meters);

// インチ毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(inch);
HAMON_UNITS_DECLARE_ACCELERATION(inches);

// フィート毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(foot);
HAMON_UNITS_DECLARE_ACCELERATION(feet);

// ヤード毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(yard);
HAMON_UNITS_DECLARE_ACCELERATION(yards);

// チェーン毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(chain);
HAMON_UNITS_DECLARE_ACCELERATION(chains);

// ハロン毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(furlong);
HAMON_UNITS_DECLARE_ACCELERATION(furlongs);

// マイル毎秒毎秒
HAMON_UNITS_DECLARE_ACCELERATION(mile);
HAMON_UNITS_DECLARE_ACCELERATION(miles);

#undef HAMON_UNITS_DECLARE_ACCELERATION_1
#undef HAMON_UNITS_DECLARE_ACCELERATION_2
#undef HAMON_UNITS_DECLARE_ACCELERATION_3
#undef HAMON_UNITS_DECLARE_ACCELERATION
#undef HAMON_UNITS_DECLARE_ACCELERATION_SI_PREFIX

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ACCELERATION_HPP
