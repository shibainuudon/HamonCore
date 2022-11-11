/**
 *	@file	sievert.hpp
 *
 *	@brief	sievert の定義
 */

#ifndef HAMON_UNITS_SIEVERT_HPP
#define HAMON_UNITS_SIEVERT_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/gram.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// シーベルト(線量当量・等価線量の単位)
template <typename T> using sievert  = decltype(joule<T>() / kilogram<T>());
template <typename T> using sieverts = sievert<T>;
HAMON_UNITS_SI_PREFIX(sievert);
HAMON_UNITS_SI_PREFIX(sieverts);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SIEVERT_HPP
