/**
 *	@file	poundal.hpp
 *
 *	@brief	poundal の定義
 */

#ifndef HAMON_UNITS_POUNDAL_HPP
#define HAMON_UNITS_POUNDAL_HPP

#include <hamon/units/pound.hpp>
#include <hamon/units/foot.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// パウンダル(lb・ft/s^2)
template <typename T> using poundal  = decltype(pound<T>() * foot<T>() / second<T>() / second<T>());
template <typename T> using poundals = poundal<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_POUNDAL_HPP
