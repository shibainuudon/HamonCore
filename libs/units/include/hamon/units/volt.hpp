/**
 *	@file	volt.hpp
 *
 *	@brief	volt の定義
 */

#ifndef HAMON_UNITS_VOLT_HPP
#define HAMON_UNITS_VOLT_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/watt.hpp>
#include <hamon/units/ampere.hpp>

namespace hamon
{

namespace units
{

// ボルト(電圧・電位差・起電力の単位)
template <typename T> using volt  = decltype(watt<T>() / ampere<T>());
template <typename T> using volts = volt<T>;
HAMON_UNITS_SI_PREFIX(volt);
HAMON_UNITS_SI_PREFIX(volts);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_VOLT_HPP
