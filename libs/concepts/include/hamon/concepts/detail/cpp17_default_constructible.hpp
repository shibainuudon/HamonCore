/**
 *	@file	cpp17_default_constructible.hpp
 *
 *	@brief	cpp17_default_constructible の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_DEFAULT_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_DEFAULT_CONSTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct cpp17_default_constructible_helper
{
	T u;

	~cpp17_default_constructible_helper();
};

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_default_constructible =
	hamon::is_object_v<T> &&
	!hamon::is_void_v<T> &&
	!hamon::is_array_v<T> &&
	requires
	{
		{ cpp17_default_constructible_helper<T>() };
		{ T() };
		{ T{} };
	};

#else

template <typename T>
struct cpp17_default_constructible_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::is_object<U>::value>,
		typename = hamon::enable_if_t<!hamon::is_void<U>::value>,
		typename = hamon::enable_if_t<!hamon::is_array<U>::value>,
		typename = decltype(cpp17_default_constructible_helper<U>()),
		typename = decltype(U()),
		typename = decltype(U{})
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using cpp17_default_constructible =
	typename cpp17_default_constructible_impl<T>::type;

#endif

template <typename T>
using cpp17_default_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_default_constructible<T>>;
#else
	hamon::detail::cpp17_default_constructible<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_DEFAULT_CONSTRUCTIBLE_HPP
