/**
 *	@file	is_specialization_of_array.hpp
 *
 *	@brief	is_specialization_of_array の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_ARRAY_HPP
#define HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <array>

namespace hamon
{

namespace detail
{

template <typename T>
struct is_specialization_of_array
	: public hamon::false_type {};

template <typename T, std::size_t N>
struct is_specialization_of_array<std::array<T, N>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_IS_SPECIALIZATION_OF_ARRAY_HPP
