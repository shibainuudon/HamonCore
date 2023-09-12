/**
 *	@file	acre.hpp
 *
 *	@brief	acre の定義
 */

#ifndef HAMON_UNITS_ACRE_HPP
#define HAMON_UNITS_ACRE_HPP

#include <hamon/units/yard.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// エーカー (4,840 平方ヤード = 4,046.8564224 平方メートル)
template <typename T> using acre  = decltype(yard<T>() * yard<T>() * hamon::ratio<4840>());
template <typename T> using acres = acre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ACRE_HPP
