/**
 *	@file	gal.hpp
 *
 *	@brief	gal の定義
 */

#ifndef HAMON_UNITS_GAL_HPP
#define HAMON_UNITS_GAL_HPP

#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ガル
template <typename T> using gal  = decltype(centimetre<T>() / second<T>() / second<T>());
template <typename T> using gals = gal<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_GAL_HPP
