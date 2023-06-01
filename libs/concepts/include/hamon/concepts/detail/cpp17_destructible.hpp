/**
 *	@file	cpp17_destructible.hpp
 *
 *	@brief	cpp17_destructible の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept cpp17_destructible =
	hamon::is_object_v<T> &&
	!hamon::is_array_v<T> &&
	requires(T u)
	{
		{ u.~T() };
	};

#else

template <typename T>
struct cpp17_destructible_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::is_object<U>::value>,
		typename = hamon::enable_if_t<!hamon::is_array<U>::value>,
		typename = decltype(hamon::declval<U>().~U())
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using cpp17_destructible =
	typename cpp17_destructible_impl<T>::type;

#endif

template <typename T>
using cpp17_destructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_destructible<T>>;
#else
	hamon::detail::cpp17_destructible<T>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_DESTRUCTIBLE_HPP
