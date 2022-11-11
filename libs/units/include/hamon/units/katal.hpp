/**
 *	@file	katal.hpp
 *
 *	@brief	katal の定義
 */

#ifndef HAMON_UNITS_KATAL_HPP
#define HAMON_UNITS_KATAL_HPP

#include <hamon/units/mole.hpp>
#include <hamon/units/second.hpp>
#include <hamon/units/detail/si_prefix.hpp>

namespace hamon
{

namespace units
{

// カタール(酵素活性（触媒活性）の単位)
template <typename T> using katal  = decltype(mole<T>() / second<T>());
template <typename T> using katals = katal<T>;
HAMON_UNITS_SI_PREFIX(katal);
HAMON_UNITS_SI_PREFIX(katals);

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_KATAL_HPP
