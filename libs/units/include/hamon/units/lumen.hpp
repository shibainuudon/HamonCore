/**
 *	@file	lumen.hpp
 *
 *	@brief	lumen の定義
 */

#ifndef HAMON_UNITS_LUMEN_HPP
#define HAMON_UNITS_LUMEN_HPP

#include <hamon/units/candela.hpp>
#include <hamon/units/steradian.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ルーメン(光束の単位)
template <typename T> using lumen  = decltype(candela<T>() * steradian<T>());
template <typename T> using lumens = lumen<T>;
HAMON_UNITS_SI_PREFIX(lumen);
HAMON_UNITS_SI_PREFIX(lumens);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_LUMEN_HPP
