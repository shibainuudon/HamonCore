/**
 *	@file	dynamic_viscosity.hpp
 *
 *	@brief	dynamic_viscosity の定義
 */

#ifndef HAMON_UNITS_DYNAMIC_VISCOSITY_HPP
#define HAMON_UNITS_DYNAMIC_VISCOSITY_HPP

#include <hamon/units/pascal.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// パスカル秒(粘度の単位)
template <typename T> using pascal_second  = decltype(pascals<T>() * second<T>());
template <typename T> using pascal_seconds = pascal_second<T>;

}	// namespace units

}	// namespace hamon

#include <hamon/units/poise.hpp>

#endif // HAMON_UNITS_DYNAMIC_VISCOSITY_HPP
