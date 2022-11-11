/**
 *	@file	magnetic_field_intensity.hpp
 *
 *	@brief	magnetic_field_intensity の定義
 */

#ifndef HAMON_UNITS_MAGNETIC_FIELD_INTENSITY_HPP
#define HAMON_UNITS_MAGNETIC_FIELD_INTENSITY_HPP

#include <hamon/units/ampere.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// アンペア毎メートル(磁場（磁界）の強さの単位)
template <typename T> using ampere_per_metre  = decltype(ampere<T>() / metre<T>());
template <typename T> using ampere_per_meter  = ampere_per_metre<T>;
template <typename T> using amperes_per_metre = ampere_per_metre<T>;
template <typename T> using amperes_per_meter = ampere_per_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MAGNETIC_FIELD_INTENSITY_HPP
