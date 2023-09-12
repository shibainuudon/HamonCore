/**
 *	@file	pound.hpp
 *
 *	@brief	pound の定義
 */

#ifndef HAMON_UNITS_POUND_HPP
#define HAMON_UNITS_POUND_HPP

#include <hamon/units/gram.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// 常用ポンド(正確に0.45359237キログラム)
template <typename T> using pound  = decltype(gram<T>() * hamon::ratio<45359237LL, 100000LL>());
template <typename T> using pounds = pound<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_POUND_HPP
