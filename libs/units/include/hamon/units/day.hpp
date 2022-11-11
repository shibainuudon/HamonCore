/**
 *	@file	day.hpp
 *
 *	@brief	day の定義
 */

#ifndef HAMON_UNITS_DAY_HPP
#define HAMON_UNITS_DAY_HPP

#include <hamon/units/hour.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 日
template <typename T> using day  = decltype(hour<T>() * std::ratio<24>());
template <typename T> using days = day<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DAY_HPP
