/**
 *	@file	momentum.hpp
 *
 *	@brief	momentum の定義
 */

#ifndef HAMON_UNITS_MOMENTUM_HPP
#define HAMON_UNITS_MOMENTUM_HPP

#include <hamon/units/newton.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// ニュートン秒(運動量の単位)
template <typename T> using newton_second  = decltype(newton<T>() * second<T>());
template <typename T> using newton_seconds = newton_second<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MOMENTUM_HPP
