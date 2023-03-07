/**
 *	@file	base_dimension_traits.hpp
 *
 *	@brief	base_dimension_traits の定義
 */

#ifndef HAMON_UNITS_DETAIL_BASE_DIMENSION_TRAITS_HPP
#define HAMON_UNITS_DETAIL_BASE_DIMENSION_TRAITS_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace units
{

template <typename T>
constexpr hamon::size_t get_type_hash() noexcept
{
	return hamon::hash(HAMON_CURRENT_FUNCTION);
}

template <typename BaseDimension>
struct base_dimension_traits
{
	HAMON_STATIC_CONSTEXPR hamon::size_t order = get_type_hash<BaseDimension>();
};

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_BASE_DIMENSION_TRAITS_HPP
