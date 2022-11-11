/**
 *	@file	hour.hpp
 *
 *	@brief	hour の定義
 */

#ifndef HAMON_UNITS_HOUR_HPP
#define HAMON_UNITS_HOUR_HPP

#include <hamon/units/minute.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 時
template <typename T> using hour  = decltype(minute<T>() * std::ratio<60>());
template <typename T> using hours = hour<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_HOUR_HPP
