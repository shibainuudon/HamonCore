/**
 *	@file	luminance.hpp
 *
 *	@brief	luminance の定義
 */

#ifndef HAMON_UNITS_LUMINANCE_HPP
#define HAMON_UNITS_LUMINANCE_HPP

#include <hamon/units/candela.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// カンデラ毎平方メートル(輝度の単位)
template <typename T> using candela_per_square_metre  = decltype(candela<T>() / metre<T>() / metre<T>());
template <typename T> using candelas_per_square_metre = candela_per_square_metre<T>;
template <typename T> using candela_per_square_meter  = candela_per_square_metre<T>;
template <typename T> using candelas_per_square_meter = candela_per_square_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_LUMINANCE_HPP
