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
concept has_member_iterator_category = requires { typename T::iterator_category; };

template <typename T>
using has_member_iterator_category_t = hamon::bool_constant<has_member_iterator_category<T>>;

#else

template <typename, typename = void>
struct has_member_iterator_category
	: public hamon::false_type {};
 
template <typename T>
struct has_member_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

template <typename T>
using has_member_iterator_category_t = has_member_iterator_category<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_HAS_MEMBER_ITERATOR_CATEGORY_HPP
