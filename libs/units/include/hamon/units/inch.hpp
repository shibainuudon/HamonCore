/**
 *	@file	inch.hpp
 *
 *	@brief	inch の定義
 */

#ifndef HAMON_UNITS_INCH_HPP
#define HAMON_UNITS_INCH_HPP

#include <hamon/units/metre.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// 国際インチ  (正確に25.4mm)
template <typename T> using inch   = decltype(metre<T>() * hamon::ratio<254, 10000>());
template <typename T> using inches = inch<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_INCH_HPP
