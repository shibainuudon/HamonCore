/**
 *	@file	is_same_or_base_of.hpp
 *
 *	@brief	is_same_or_base_of の定義
 */

#ifndef HAMON_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP
#define HAMON_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T0, typename T1>
struct is_same_or_base_of
	: public hamon::bool_constant<
		std::is_same<T0, T1>::value ||
		std::is_base_of<T0, T1>::value
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_DETAIL_IS_SAME_OR_BASE_OF_HPP
