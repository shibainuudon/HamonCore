/**
 *	@file	litre.hpp
 *
 *	@brief	litre の定義
 */

#ifndef HAMON_UNITS_LITRE_HPP
#define HAMON_UNITS_LITRE_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// リットル
template <typename T> using litre  = decltype(decimetre<T>() * decimetre<T>() * decimetre<T>());
template <typename T> using litres = litre<T>;
template <typename T> using liter  = litre<T>;
template <typename T> using liters = litre<T>;
HAMON_UNITS_SI_PREFIX(litre);
HAMON_UNITS_SI_PREFIX(litres);
HAMON_UNITS_SI_PREFIX(liter);
HAMON_UNITS_SI_PREFIX(liters);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_LITRE_HPP
