/**
 *	@file	bit.hpp
 *
 *	@brief	bit の定義
 */

#ifndef HAMON_UNITS_BIT_HPP
#define HAMON_UNITS_BIT_HPP

#include <hamon/units/base_dimensions/information.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/detail/binary_prefix.hpp>

namespace hamon
{

namespace units
{

// ビット
template <typename T> using bit  = quantity<T, information_dimension>;
template <typename T> using bits = bit<T>;
HAMON_UNITS_SI_PREFIX(bit);
HAMON_UNITS_SI_PREFIX(bits);
HAMON_UNITS_BINARY_PREFIX(bit);
HAMON_UNITS_BINARY_PREFIX(bits);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_BIT_HPP
