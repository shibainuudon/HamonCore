/**
 *	@file	power.hpp
 *
 *	@brief	power の定義
 */

#ifndef HAMON_UNITS_POWER_HPP
#define HAMON_UNITS_POWER_HPP

#include <hamon/units/erg.hpp>
#include <hamon/units/foot_poundal.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// エルグ毎秒
template <typename T> using erg_per_second  = decltype(erg<T>() / second<T>());
template <typename T> using ergs_per_second = erg_per_second<T>;

// フィート・パウンダル毎秒
template <typename T> using foot_poundal_per_second = decltype(foot_poundal<T>() / second<T>());
template <typename T> using feet_poundal_per_second = foot_poundal_per_second<T>;

}	// namespace units

}	// namespace hamon

#include <hamon/units/watt.hpp>

#endif // HAMON_UNITS_POWER_HPP
