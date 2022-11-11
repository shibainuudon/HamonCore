/**
 *	@file	mole.hpp
 *
 *	@brief	mole の定義
 */

#ifndef HAMON_UNITS_MOLE_HPP
#define HAMON_UNITS_MOLE_HPP

#include <hamon/units/base_dimensions/amount.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// モル
template <typename T> using mole  = quantity<T, amount_dimension>;
template <typename T> using moles = mole<T>;
HAMON_UNITS_SI_PREFIX(mole);
HAMON_UNITS_SI_PREFIX(moles);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MOLE_HPP
