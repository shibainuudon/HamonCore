/**
 *	@file	has_member_iterator_category.hpp
 *
 *	@brief	has_member_iterator_category の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_HAS_MEMBER_ITERATOR_CATEGORY_HPP
#define HAMON_ITERATOR_DETAIL_HAS_MEMBER_ITERATOR_CATEGORY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_iterator_category = requires { typename T::iterator_category; };

#else

template <typename, typename = void>
struct has_member_iterator_category_impl
	: public hamon::false_type {};
 
template <typename T>
struct has_member_iterator_category_impl<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_iterator_category =
	detail::has_member_iterator_category_impl<T>::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_HAS_MEMBER_ITERATOR_CATEGORY_HPP
