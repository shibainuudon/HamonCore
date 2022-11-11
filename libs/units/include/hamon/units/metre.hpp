/**
 *	@file	metre.hpp
 *
 *	@brief	metre の定義
 */

#ifndef HAMON_UNITS_METRE_HPP
#define HAMON_UNITS_METRE_HPP

#include <hamon/units/base_dimensions/length.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// メートル
template <typename T> using metre  = quantity<T, length_dimension>;
template <typename T> using metres = metre<T>;
template <typename T> using meter  = metre<T>;
template <typename T> using meters = metre<T>;
HAMON_UNITS_SI_PREFIX(metre);
HAMON_UNITS_SI_PREFIX(metres);
HAMON_UNITS_SI_PREFIX(meter);
HAMON_UNITS_SI_PREFIX(meters);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_METRE_HPP
