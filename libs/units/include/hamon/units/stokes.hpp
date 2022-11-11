/**
 *	@file	stokes.hpp
 *
 *	@brief	stokes の定義
 */

#ifndef HAMON_UNITS_STOKES_HPP
#define HAMON_UNITS_STOKES_HPP

#include <hamon/units/second.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ストークス(動粘度の単位)
template <typename T> using stokes = decltype(centimetre<T>() * centimetre<T>() / second<T>());
// ※単数形・複数形ともstokes

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_STOKES_HPP
