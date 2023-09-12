/**
 *	@file	grain.hpp
 *
 *	@brief	grain の定義
 */

#ifndef HAMON_UNITS_GRAIN_HPP
#define HAMON_UNITS_GRAIN_HPP

#include <hamon/units/pound.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// グレーン = 1/7000常用ポンド(正確に0.06479891グラム)
template <typename T> using grain  = decltype(pound<T>() * hamon::ratio<1, 7000>());
template <typename T> using grains = grain<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_GRAIN_HPP
