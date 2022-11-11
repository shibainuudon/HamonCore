/**
 *	@file	minute.hpp
 *
 *	@brief	minute の定義
 */

#ifndef HAMON_UNITS_MINUTE_HPP
#define HAMON_UNITS_MINUTE_HPP

#include <hamon/units/second.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 分
template <typename T> using minute  = decltype(second<T>() * std::ratio<60>());
template <typename T> using minutes = minute<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MINUTE_HPP
