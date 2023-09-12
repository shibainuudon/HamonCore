/**
 *	@file	dimensionless.hpp
 *
 *	@brief	dimensionless の定義
 */

#ifndef HAMON_UNITS_QUANTITY_DIMENSIONLESS_HPP
#define HAMON_UNITS_QUANTITY_DIMENSIONLESS_HPP

#include <hamon/units/quantity/quantity_fwd.hpp>
#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/ratio/ratio.hpp>

namespace hamon
{

namespace units
{

// dimensionless
template <typename T, typename Scale = hamon::ratio<1>>
using dimensionless = quantity<T, derived_dimension<>, Scale>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_QUANTITY_DIMENSIONLESS_HPP
