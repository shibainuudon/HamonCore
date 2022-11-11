/**
 *	@file	candela.hpp
 *
 *	@brief	candela の定義
 */

#ifndef HAMON_UNITS_CANDELA_HPP
#define HAMON_UNITS_CANDELA_HPP

#include <hamon/units/base_dimensions/luminous_intensity.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// カンデラ
template <typename T> using candela  = quantity<T, luminous_intensity_dimension>;
template <typename T> using candelas = candela<T>;
HAMON_UNITS_SI_PREFIX(candela);
HAMON_UNITS_SI_PREFIX(candelas);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_CANDELA_HPP
