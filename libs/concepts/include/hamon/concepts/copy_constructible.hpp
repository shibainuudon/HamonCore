/**
 *	@file	copy_constructible.hpp
 *
 *	@brief	copy_constructible の定義
 */

#ifndef HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#endif

namespace hamon
{

// 18.4.14 Concept copy_constructible	[concept.copyconstructible]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::copy_constructible;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept copy_constructible =
	hamon::move_constructible<T> &&
	hamon::constructible_from<T, T&>       && hamon::convertible_to<T&, T> &&
	hamon::constructible_from<T, T const&> && hamon::convertible_to<T const&, T> &&
	hamon::constructible_from<T, T const>  && hamon::convertible_to<T const, T>;

#else

namespace detail
{

template <typename T>
struct copy_constructible_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::move_constructible_t<U>::value &&
			hamon::constructible_from_t<U, U&>::value       && hamon::convertible_to<U&, U> &&
			hamon::constructible_from_t<U, U const&>::value && hamon::convertible_to<U const&, U> &&
			hamon::constructible_from_t<U, U const>::value  && hamon::convertible_to<U const, U>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using copy_constructible =
	typename detail::copy_constructible_impl<T>::type;

#endif

template <typename T>
using copy_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::copy_constructible<T>>;
#else
	hamon::copy_constructible<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
