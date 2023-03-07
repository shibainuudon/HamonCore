/**
 *	@file	incrementable_traits.hpp
 *
 *	@brief	incrementable_traits の定義
 */

#ifndef HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP
#define HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{

using std::incrementable_traits;

}	// namespace hamon

#else

#include <hamon/iterator/concepts/detail/has_difference_type.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_pointer.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/make_signed.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

// (1) Primary template
template <typename, typename = void, typename = void>
struct incrementable_traits {};

// (2) Specialization for pointers
template <typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::is_object<T>::value
#endif
struct incrementable_traits<T*
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<hamon::is_object<T>::value>
#endif
>
{
	using difference_type = std::ptrdiff_t;
};

// (3) Specialization for const-qualified types
template <typename Iter>
struct incrementable_traits<Iter const>
	: public incrementable_traits<Iter> {};

// (4) Specialization for types that define a public and accessible member type difference_type
template <typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires requires { typename T::difference_type; }
#endif
struct incrementable_traits<T
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<
		!hamon::is_const<T>::value &&
		!hamon::is_pointer<T>::value &&
		detail::has_difference_type<T>::value
	>
#endif
>
{
	using difference_type = typename T::difference_type;
};

// GCC 10 だと 下の
// { a - b } -> hamon::integral;
// の行で error: invalid use of ‘void’
// のエラーになってしまうのでそれを回避する
#if defined(__GNUC__) && (__GNUC__ == 10)
#define HAMON_GCC_10	1
#else
#define HAMON_GCC_10	0
#endif

// (5) Specialization for types that do not define a public and accessible member type difference_type
//     but do support subtraction
template <typename T>
#if defined(HAMON_HAS_CXX20_CONCEPTS) && !HAMON_GCC_10
requires (
	!requires { typename T::difference_type; } &&
	requires(T const& a, T const& b)
	{
		{ a - b } -> hamon::integral;
	})
#endif
struct incrementable_traits<T
#if !(defined(HAMON_HAS_CXX20_CONCEPTS) && !HAMON_GCC_10)
	, hamon::enable_if_t<
		!hamon::is_const<T>::value &&
		!hamon::is_pointer<T>::value &&
		!detail::has_difference_type<T>::value
	>
	, hamon::enable_if_t<
		hamon::integral_t<decltype(hamon::declval<T>() - hamon::declval<T>())>::value
	>
#endif
>
{
	using difference_type = hamon::make_signed_t<decltype(hamon::declval<T>() - hamon::declval<T>())>;
};

#undef HAMON_GCC_10

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_INCREMENTABLE_TRAITS_HPP
