/**
 *	@file	has_member_difference_type.hpp
 *
 *	@brief	has_member_difference_type の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_HAS_MEMBER_DIFFERENCE_TYPE_HPP
#define HAMON_ITERATOR_DETAIL_HAS_MEMBER_DIFFERENCE_TYPE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_difference_type = requires { typename T::difference_type; };

template <typename T>
using has_member_difference_type_t = hamon::bool_constant<has_member_difference_type<T>>;

#else

template <typename, typename = void>
struct has_member_difference_type
	: public hamon::false_type {};
 
template <typename T>
struct has_member_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public hamon::true_type {};

template <typename T>
using has_member_difference_type_t = has_member_difference_type<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_HAS_MEMBER_DIFFERENCE_TYPE_HPP
