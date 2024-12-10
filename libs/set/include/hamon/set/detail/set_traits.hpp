/**
 *	@file	set_traits.hpp
 *
 *	@brief
 */

#ifndef HAMON_SET_DETAIL_SET_TRAITS_HPP
#define HAMON_SET_DETAIL_SET_TRAITS_HPP

#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cvref.hpp>

namespace hamon
{

namespace detail
{

template <typename ValueType, typename SizeType, typename DifferenceType, bool Multi>
struct set_traits
{
	using value_type = ValueType;
	using size_type = SizeType;
	using difference_type = DifferenceType;
	static const bool multi = Multi;

	template <typename Arg>
	using in_place_comparable = hamon::is_same<ValueType, hamon::remove_cvref_t<Arg>>;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SET_DETAIL_SET_TRAITS_HPP
