/**
 *	@file	second.hpp
 *
 *	@brief	second の定義
 */

#ifndef HAMON_UNITS_SECOND_HPP
#define HAMON_UNITS_SECOND_HPP

#include <hamon/units/base_dimensions/time.hpp>
#include <hamon/units/quantity.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// 秒
template <typename T> using second  = quantity<T, time_dimension>;
template <typename T> using seconds = second<T>;
HAMON_UNITS_SI_PREFIX(second);
HAMON_UNITS_SI_PREFIX(seconds);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SECOND_HPP
