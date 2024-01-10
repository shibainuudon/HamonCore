/**
 *	@file	indirectly_readable_traits.hpp
 *
 *	@brief	indirectly_readable_traits の定義
 */

#ifndef HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
#define HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#define HAMON_INDIRECTLY_READABLE_TRAITS_NAMESPACE  std

namespace hamon
{

using std::indirectly_readable_traits;

}	// namespace hamon

#else

#include <hamon/iterator/detail/has_member_value_type.hpp>
#include <hamon/iterator/detail/has_member_element_type.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_extent.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_object.hpp>

#define HAMON_INDIRECTLY_READABLE_TRAITS_NAMESPACE  hamon

namespace hamon
{

namespace detail
{

template <typename T, bool = hamon::is_object<T>::value>
struct cond_value_type {};

template <typename T>
struct cond_value_type<T, true>
{
	using value_type = hamon::remove_cv_t<T>;
};

template <typename T,
	bool = hamon::is_array<T>::value,
	bool = hamon::detail::has_member_value_type_t<T>::value,
	bool = hamon::detail::has_member_element_type_t<T>::value
>
struct indirectly_readable_traits_impl {};

template <typename T, bool B1, bool B2>
struct indirectly_readable_traits_impl<T, true, B1, B2>
{
	using value_type = hamon::remove_cv_t<hamon::remove_extent_t<T>>;
};

template <typename T>
struct indirectly_readable_traits_impl<T, false, true, false>
	: public hamon::detail::cond_value_type<typename T::value_type> {};

template <typename T>
struct indirectly_readable_traits_impl<T, false, false, true>
	: public hamon::detail::cond_value_type<typename T::element_type> {};

template <typename T>
struct indirectly_readable_traits_impl<T, false, true, true>
	: public hamon::detail::cond_value_type<
		hamon::conditional_t<
			hamon::same_as_t<
				hamon::remove_cv_t<typename T::element_type>,
				hamon::remove_cv_t<typename T::value_type>
			>::value,
			hamon::remove_cv_t<typename T::value_type>,
			void
		>
	>
{};

}	// namespace detail

template <typename T>
struct indirectly_readable_traits
	: public hamon::detail::indirectly_readable_traits_impl<T> {};

template <typename T>
struct indirectly_readable_traits<T*>
	: public hamon::detail::cond_value_type<T> {};

template <typename I>
struct indirectly_readable_traits<I const>
	: public indirectly_readable_traits<I> {};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INDIRECTLY_READABLE_TRAITS_HPP
