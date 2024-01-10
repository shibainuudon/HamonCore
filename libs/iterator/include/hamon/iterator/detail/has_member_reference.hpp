/**
 *	@file	has_member_reference.hpp
 *
 *	@brief	has_member_reference の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_HAS_MEMBER_REFERENCE_HPP
#define HAMON_ITERATOR_DETAIL_HAS_MEMBER_REFERENCE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_member_reference = requires { typename T::reference; };

template <typename T>
using has_member_reference_t = hamon::bool_constant<has_member_reference<T>>;

#else

template <typename, typename = void>
struct has_member_reference
	: public hamon::false_type {};
 
template <typename T>
struct has_member_reference<T, hamon::void_t<typename T::reference>>
	: public hamon::true_type {};

template <typename T>
using has_member_reference_t = has_member_reference<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_HAS_MEMBER_REFERENCE_HPP
