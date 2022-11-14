﻿/**
 *	@file	degree.hpp
 *
 *	@brief	degree の定義
 */

#ifndef HAMON_UNITS_DEGREE_HPP
#define HAMON_UNITS_DEGREE_HPP

#include <hamon/units/base_dimensions/angle.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/radian.hpp>
#include <ratio>

namespace hamon
{

namespace units
{

// 度数法
template <typename T> using degree  = quantity<T, angle_dimension, std::ratio<2646693125139304345LL / 180, 842468587426513207LL>>;
template <typename T> using degrees = degree<T>;

/**
 *	@brief	sinのオーバーロード
 */
template <typename T>
inline T sin(degrees<T> const& d)
{
	return sin(radians<T>(d));
}

/**
 *	@brief	cosのオーバーロード
 */
template <typename T>
inline T cos(degrees<T> const& d)
{
	return cos(radians<T>(d));
}

/**
 *	@brief	tanのオーバーロード
 */
template <typename T>
inline T tan(degrees<T> const& d)
{
	return tan(radians<T>(d));
}

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DEGREE_HPP
