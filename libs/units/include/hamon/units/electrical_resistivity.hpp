/**
 *	@file	electrical_resistivity.hpp
 *
 *	@brief	electrical_resistivity の定義
 */

#ifndef HAMON_UNITS_ELECTRICAL_RESISTIVITY_HPP
#define HAMON_UNITS_ELECTRICAL_RESISTIVITY_HPP

#include <hamon/units/ohm.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// オームメートル(電気抵抗率の単位)
template <typename T> using ohm_metre = decltype(ohm<T>() * metre<T>());
template <typename T> using ohm_meter = ohm_metre<T>;

// オームセンチメートル
template <typename T> using ohm_centimetre = decltype(ohm<T>() * centimetre<T>());
template <typename T> using ohm_centimeter = ohm_centimetre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ELECTRICAL_RESISTIVITY_HPP
