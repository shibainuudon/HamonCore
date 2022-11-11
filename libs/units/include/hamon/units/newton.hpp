/**
 *	@file	newton.hpp
 *
 *	@brief	newton の定義
 */

#ifndef HAMON_UNITS_NEWTON_HPP
#define HAMON_UNITS_NEWTON_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/gram.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ニュートン(kg・m/s^2)
template <typename T> using newton  = decltype(kilogram<T>() * metre<T>() / second<T>() / second<T>());
template <typename T> using newtons = newton<T>;
HAMON_UNITS_SI_PREFIX(newton);
HAMON_UNITS_SI_PREFIX(newtons);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_NEWTON_HPP
