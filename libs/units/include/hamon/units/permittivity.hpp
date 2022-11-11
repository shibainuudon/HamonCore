/**
 *	@file	permittivity.hpp
 *
 *	@brief	permittivity の定義
 */

#ifndef HAMON_UNITS_PERMITTIVITY_HPP
#define HAMON_UNITS_PERMITTIVITY_HPP

#include <hamon/units/farad.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ファラド毎メートル(誘電率の単位)
template <typename T> using farad_per_metre  = decltype(farad<T>() / metre<T>());
template <typename T> using farad_per_meter  = farad_per_metre<T>;
template <typename T> using farads_per_metre = farad_per_metre<T>;
template <typename T> using farads_per_meter = farad_per_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_PERMITTIVITY_HPP
