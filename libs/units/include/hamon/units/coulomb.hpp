/**
 *	@file	coulomb.hpp
 *
 *	@brief	coulomb の定義
 */

#ifndef HAMON_UNITS_COULOMB_HPP
#define HAMON_UNITS_COULOMB_HPP

#include <hamon/units/detail/si_prefix.hpp>
#include <hamon/units/ampere.hpp>
#include <hamon/units/second.hpp>

namespace hamon
{

namespace units
{

// クーロン(電荷の単位)
template <typename T> using coulomb  = decltype(ampere<T>() * second<T>());
template <typename T> using coulombs = coulomb<T>;
HAMON_UNITS_SI_PREFIX(coulomb);
HAMON_UNITS_SI_PREFIX(coulombs);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_COULOMB_HPP
