/**
 *	@file	erg.hpp
 *
 *	@brief	erg の定義
 */

#ifndef HAMON_UNITS_ERG_HPP
#define HAMON_UNITS_ERG_HPP

#include <hamon/units/dyne.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// エルグ(dyn・cm)
template <typename T> using erg  = decltype(dyne<T>() * centimetre<T>());
template <typename T> using ergs = erg<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ERG_HPP
