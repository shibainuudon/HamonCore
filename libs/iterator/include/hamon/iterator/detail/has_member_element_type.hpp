/**
 *	@file	has_member_element_type.hpp
 *
 *	@brief	has_member_element_type の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_HAS_MEMBER_ELEMENT_TYPE_HPP
#define HAMON_ITERATOR_DETAIL_HAS_MEMBER_ELEMENT_TYPE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_element_type = requires { typename T::element_type; };

#else

template <typename, typename = void>
struct has_member_element_type_impl
	: public hamon::false_type {};
 
template <typename T>
struct has_member_element_type_impl<T, hamon::void_t<typename T::element_type>>
	: public hamon::true_type {};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_element_type =
	detail::has_member_element_type_impl<T>::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_HAS_MEMBER_ELEMENT_TYPE_HPP
