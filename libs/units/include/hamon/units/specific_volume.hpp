﻿/**
 *	@file	specific_volume.hpp
 *
 *	@brief	specific_volume の定義
 */

#ifndef HAMON_UNITS_SPECIFIC_VOLUME_HPP
#define HAMON_UNITS_SPECIFIC_VOLUME_HPP

#include <hamon/units/metre.hpp>
#include <hamon/units/gram.hpp>

namespace hamon
{

namespace units
{

// 立方メートル毎キログラム(比容積の単位)
template <typename T> using cubic_metre_per_kilogram  = decltype(metre<T>() * metre<T>() * metre<T>() / kilogram<T>());
template <typename T> using cubic_meter_per_kilogram  = cubic_metre_per_kilogram<T>;
template <typename T> using cubic_metres_per_kilogram = cubic_metre_per_kilogram<T>;
template <typename T> using cubic_meters_per_kilogram = cubic_metre_per_kilogram<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SPECIFIC_VOLUME_HPP
