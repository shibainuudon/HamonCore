/**
 *	@file	dimension_holder.hpp
 *
 *	@brief	dimension_holder の定義
 */

#ifndef HAMON_UNITS_DETAIL_DIMENSION_HOLDER_HPP
#define HAMON_UNITS_DETAIL_DIMENSION_HOLDER_HPP

#include <hamon/units/detail/dimension_holder_fwd.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

template <typename Dimension, int Power>
struct dimension_holder
{
	using type = Dimension;
	HAMON_STATIC_CONSTEXPR int power = Power;
};

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_DIMENSION_HOLDER_HPP
