/**
 *	@file	watt.hpp
 *
 *	@brief	watt の定義
 */

#ifndef HAMON_UNITS_WATT_HPP
#define HAMON_UNITS_WATT_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/joule.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ワット(J/s)
template <typename T> using watt  = decltype(joule<T>() / second<T>());
template <typename T> using watts = watt<T>;
HAMON_UNITS_SI_PREFIX(watt);
HAMON_UNITS_SI_PREFIX(watts);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_WATT_HPP
