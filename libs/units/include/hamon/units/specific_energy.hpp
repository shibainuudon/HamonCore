/**
 *	@file	specific_energy.hpp
 *
 *	@brief	specific_energy の定義
 */

#ifndef HAMON_UNITS_SPECIFIC_ENERGY_HPP
#define HAMON_UNITS_SPECIFIC_ENERGY_HPP

#include <hamon/units/joule.hpp>
#include <hamon/units/gram.hpp>

namespace hamon
{

namespace units
{

// ジュール毎キログラム(比エネルギーの単位)
template <typename T> using joule_per_kilogram  = decltype(joule<T>() / kilogram<T>());
template <typename T> using joules_per_kilogram = joule_per_kilogram<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_SPECIFIC_ENERGY_HPP
