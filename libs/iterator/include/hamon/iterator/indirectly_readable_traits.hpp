/**
 *	@file	indirectly_readable_traits.hpp
 *
 *	@brief	indirectly_readable_traits の定義
 */

#ifndef HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
#define HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::indirectly_readable_traits;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/detail/has_value_type.hpp>
#include <hamon/iterator/concepts/detail/has_element_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T, bool = std::is_object<T>::value>
struct cond_value_type {};

template <typename T>
struct cond_value_type<T, true>
{
	using value_type = typename std::remove_cv<T>::type;
};

}	// namespace detail

// (1) Primary template
template <typename I, typename = void>
struct indirectly_readable_traits {};

// (2) Specialization for pointers
template <typename T>
struct indirectly_readable_traits<T*>
	: public detail::cond_value_type<T> {};

// (3) Specialization for array types
template <typename T>
struct indirectly_readable_traits<T, hamon::enable_if_t<!std::is_const<T>::value && std::is_array<T>::value>>
{
	using value_type = typename std::remove_cv<typename std::remove_extent<T>::type>::type;
};

// (4) Specialization for const-qualified types
template <typename I>
struct indirectly_readable_traits<const I>
	: public indirectly_readable_traits<I> {};

// (5) Specialization for types that define a public and accessible member type value_type
template <typename T>
struct indirectly_readable_traits<T, hamon::enable_if_t<!std::is_const<T>::value && detail::has_value_type<T>::value>>
	: public detail::cond_value_type<typename T::value_type> {};

// (6) Specialization for types that define a public and accessible member type element_type
template <typename T>
struct indirectly_readable_traits<T, hamon::enable_if_t<!std::is_const<T>::value && detail::has_element_type<T>::value>>
	: public detail::cond_value_type<typename T::element_type> {};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
