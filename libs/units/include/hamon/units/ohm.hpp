/**
 *	@file	ohm.hpp
 *
 *	@brief	ohm の定義
 */

#ifndef HAMON_UNITS_OHM_HPP
#define HAMON_UNITS_OHM_HPP

#include <hamon/units/volt.hpp>
#include <hamon/units/ampere.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// オーム(電気抵抗の単位)
template <typename T> using ohm  = decltype(volt<T>() / ampere<T>());
template <typename T> using ohms = ohm<T>;
HAMON_UNITS_SI_PREFIX(ohm);
HAMON_UNITS_SI_PREFIX(ohms);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_OHM_HPP
