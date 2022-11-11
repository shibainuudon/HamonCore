/**
 *	@file	derived_dimension.hpp
 *
 *	@brief	derived_dimension の定義
 */

#ifndef HAMON_UNITS_DETAIL_DERIVED_DIMENSION_HPP
#define HAMON_UNITS_DETAIL_DERIVED_DIMENSION_HPP

#include <hamon/units/detail/derived_dimension_fwd.hpp>

namespace hamon
{

namespace units
{

template <typename... BaseDimensions>
struct derived_dimension
{
//	using type = typename make_derived_dimension<BaseDimensions...>::type;
};

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_DERIVED_DIMENSION_HPP
