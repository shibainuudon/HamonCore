/**
 *	@file	poise.hpp
 *
 *	@brief	poise の定義
 */

#ifndef HAMON_UNITS_POISE_HPP
#define HAMON_UNITS_POISE_HPP

#include <hamon/units/dyne.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/metre.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// ポアズ(粘度の単位)
template <typename T> using poise  = decltype(dyne<T>() * second<T>() / (centimetre<T>() * centimetre<T>()));
template <typename T> using poises = poise<T>;
HAMON_UNITS_SI_PREFIX(poise);
HAMON_UNITS_SI_PREFIX(poises);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_POISE_HPP
