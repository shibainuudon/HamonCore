﻿/**
 *	@file	year.hpp
 *
 *	@brief	year の定義
 */

#ifndef HAMON_UNITS_YEAR_HPP
#define HAMON_UNITS_YEAR_HPP

#include <hamon/units/day.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// 年　= 365.25 日	(ユリウス年)
template <typename T> using year  = decltype(day<T>() * hamon::ratio<36525, 100>());
template <typename T> using years = year<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_YEAR_HPP
