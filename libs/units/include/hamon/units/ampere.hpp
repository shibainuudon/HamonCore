/**
 *	@file	ampere.hpp
 *
 *	@brief	ampere の定義
 */

#ifndef HAMON_UNITS_AMPERE_HPP
#define HAMON_UNITS_AMPERE_HPP

#include <hamon/units/base_dimensions/current.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// アンペア
template <typename T> using ampere  = quantity<T, current_dimension>;
template <typename T> using amperes = ampere<T>;
HAMON_UNITS_SI_PREFIX(ampere);
HAMON_UNITS_SI_PREFIX(amperes);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_AMPERE_HPP
