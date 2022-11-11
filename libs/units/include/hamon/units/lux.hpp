/**
 *	@file	lux.hpp
 *
 *	@brief	lux の定義
 */

#ifndef HAMON_UNITS_LUX_HPP
#define HAMON_UNITS_LUX_HPP

#include <hamon/units/lumen.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ルクス(照度の単位)
template <typename T> using lux  = decltype(lumen<T>() / metre<T>() / metre<T>());
HAMON_UNITS_SI_PREFIX(lux);
// ※単数形・複数形ともlux

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_LUX_HPP
