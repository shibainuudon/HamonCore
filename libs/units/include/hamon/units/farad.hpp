/**
 *	@file	farad.hpp
 *
 *	@brief	farad の定義
 */

#ifndef HAMON_UNITS_FARAD_HPP
#define HAMON_UNITS_FARAD_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/coulomb.hpp>
#include <hamon/units/volt.hpp>

namespace hamon
{

namespace units
{

// ファラド(静電容量の単位)
template <typename T> using farad  = decltype(coulomb<T>() / volt<T>());
template <typename T> using farads = farad<T>;
HAMON_UNITS_SI_PREFIX(farad);
HAMON_UNITS_SI_PREFIX(farads);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_FARAD_HPP
