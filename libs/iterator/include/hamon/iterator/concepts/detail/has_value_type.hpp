/**
 *	@file	has_value_type.hpp
 *
 *	@brief	has_value_type の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename, typename = void>
struct has_value_type
	: public hamon::false_type {};
 
template <typename T>
struct has_value_type<T, hamon::void_t<typename T::value_type>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_VALUE_TYPE_HPP
