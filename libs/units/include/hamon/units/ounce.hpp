/**
 *	@file	ounce.hpp
 *
 *	@brief	ounce の定義
 */

#ifndef HAMON_UNITS_OUNCE_HPP
#define HAMON_UNITS_OUNCE_HPP

#include <hamon/units/pound.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// 常用オンス = 1/16常用ポンド (正確に28.349523125グラム)
template <typename T> using ounce  = decltype(pound<T>() * hamon::ratio<1, 16>());
template <typename T> using ounces = ounce<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_OUNCE_HPP
