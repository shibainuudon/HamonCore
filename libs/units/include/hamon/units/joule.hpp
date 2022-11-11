/**
 *	@file	joule.hpp
 *
 *	@brief	joule の定義
 */

#ifndef HAMON_UNITS_JOULE_HPP
#define HAMON_UNITS_JOULE_HPP

#include <hamon/units/newton.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ジュール(kg・m^2 / s^2 = N・m)
template <typename T> using joule  = decltype(newton<T>() * metre<T>());
template <typename T> using joules = joule<T>;
HAMON_UNITS_SI_PREFIX(joule);
HAMON_UNITS_SI_PREFIX(joules);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_JOULE_HPP
