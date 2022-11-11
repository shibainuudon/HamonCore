/**
 *	@file	gram.hpp
 *
 *	@brief	gram の定義
 */

#ifndef HAMON_UNITS_GRAM_HPP
#define HAMON_UNITS_GRAM_HPP

#include <hamon/units/base_dimensions/mass.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// グラム
template <typename T> using gram  = quantity<T, mass_dimension>;
template <typename T> using grams = gram<T>;
HAMON_UNITS_SI_PREFIX(gram);
HAMON_UNITS_SI_PREFIX(grams);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_GRAM_HPP
