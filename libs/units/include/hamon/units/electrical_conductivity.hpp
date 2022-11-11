/**
 *	@file	electrical_conductivity.hpp
 *
 *	@brief	electrical_conductivity の定義
 */

#ifndef HAMON_UNITS_ELECTRICAL_CONDUCTIVITY_HPP
#define HAMON_UNITS_ELECTRICAL_CONDUCTIVITY_HPP

#include <hamon/units/siemens.hpp>
#include <hamon/units/metre.hpp>

namespace hamon
{

namespace units
{

// ジーメンス毎メートル(電気伝導率の単位)
template <typename T> using siemens_per_metre = decltype(siemens<T>() / metre<T>());
template <typename T> using siemens_per_meter = siemens_per_metre<T>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_ELECTRICAL_CONDUCTIVITY_HPP
