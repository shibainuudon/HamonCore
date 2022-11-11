/**
 *	@file	dimension_divide.hpp
 *
 *	@brief	dimension_divide の定義
 */

#ifndef HAMON_UNITS_DETAIL_DIMENSION_DIVIDE_HPP
#define HAMON_UNITS_DETAIL_DIMENSION_DIVIDE_HPP

#include <hamon/units/detail/dimension_multiply.hpp>
#include <hamon/units/detail/dimension_inverse.hpp>

namespace hamon
{

namespace units
{

/**
 *	@brief	derived_dimension同士を除算して新しいderived_dimensionを得る
 */
template <typename D1, typename D2>
using dimension_divide = dimension_multiply<D1, dimension_inverse<D2>>;

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_DIMENSION_DIVIDE_HPP
