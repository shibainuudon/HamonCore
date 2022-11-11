/**
 *	@file	foot_poundal.hpp
 *
 *	@brief	foot_poundal の定義
 */

#ifndef HAMON_UNITS_FOOT_POUNDAL_HPP
#define HAMON_UNITS_FOOT_POUNDAL_HPP

#include <hamon/units/poundal.hpp>
#include <hamon/units/foot.hpp>

namespace hamon
{

namespace units
{

// フィート・パウンダル
template <typename T> using foot_poundal = decltype(poundal<T>() * foot<T>());
template <typename T> using feet_poundal = foot_poundal<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_FOOT_POUNDAL_HPP
