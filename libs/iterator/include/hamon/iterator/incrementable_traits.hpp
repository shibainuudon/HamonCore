/**
 *	@file	incrementable_traits.hpp
 *
 *	@brief	incrementable_traits の定義
 */

#ifndef HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

#define HAMON_INCREMENTABLE_TRAITS_NAMESPACE  std

namespace hamon
{

using std::incrementable_traits;

}	// namespace hamon

#else

#include <hamon/iterator/detail/has_member_difference_type.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/utility/declval.hpp>

#define HAMON_INCREMENTABLE_TRAITS_NAMESPACE  hamon

namespace hamon
{

namespace detail
{

template <typename T, bool = hamon::is_object<T>::value>
struct cond_difference_type {};

template <typename T>
struct cond_difference_type<T, true>
{
	using difference_type = hamon::ptrdiff_t;
};

template <typename T,
	bool = hamon::detail::has_member_difference_type_t<T>::value,
	typename = void
>
struct incrementable_traits_impl {};

template <typename T>
struct incrementable_traits_impl<T, true>
{
	using difference_type = typename T::difference_type;
};

template <typename T>
struct incrementable_traits_impl<T, false,
	hamon::enable_if_t<
		hamon::integral_t<decltype(hamon::declval<T>() - hamon::declval<T>())>::value
	>>
{
	using difference_type = hamon::make_signed_t<decltype(hamon::declval<T>() - hamon::declval<T>())>;
};

}	// namespace detail

// 25.3.2.1 Incrementable traits[incrementable.traits]

template <typename T>
struct incrementable_traits
	: public hamon::detail::incrementable_traits_impl<T> {};

template <typename T>
struct incrementable_traits<T*>
	: public hamon::detail::cond_difference_type<T> {};

template <typename I>
struct incrementable_traits<I const>
	: public incrementable_traits<I> {};

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP
