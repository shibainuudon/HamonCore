/**
 *	@file	is_specialization_of_tuple.hpp
 *
 *	@brief	is_specialization_of_tuple の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_TUPLE_HPP
#define HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_TUPLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <tuple>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_tuple
	: public hamon::false_type {};

template <typename... Types>
struct is_specialization_of_tuple<std::tuple<Types...>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_TUPLE_HPP
