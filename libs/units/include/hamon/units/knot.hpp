/**
 *	@file	knot.hpp
 *
 *	@brief	knot の定義
 */

#ifndef HAMON_UNITS_KNOT_HPP
#define HAMON_UNITS_KNOT_HPP

#include <hamon/units/metre.hpp>
#include <hamon/units/second.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// ノット
template <typename T> using knot  = decltype(metre<T>() / second<T>() * std::ratio<1852, 3600>());
template <typename T> using knots = knot<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_KNOT_HPP
