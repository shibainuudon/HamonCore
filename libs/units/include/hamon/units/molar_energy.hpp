/**
 *	@file	molar_energy.hpp
 *
 *	@brief	molar_energy の定義
 */

#ifndef HAMON_UNITS_MOLAR_ENERGY_HPP
#define HAMON_UNITS_MOLAR_ENERGY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/mole.hpp>

namespace hamon
{

namespace units
{

// ジュール毎モル(モルエネルギーの単位)
template <typename T> using joule_per_mole  = decltype(joule<T>() / mole<T>());
template <typename T> using joules_per_mole = joule_per_mole<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_MOLAR_ENERGY_HPP
