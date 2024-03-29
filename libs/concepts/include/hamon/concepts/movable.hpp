﻿/**
 *	@file	movable.hpp
 *
 *	@brief	movable の定義
 */

#ifndef HAMON_CONCEPTS_MOVABLE_HPP
#define HAMON_CONCEPTS_MOVABLE_HPP

#include <hamon/concepts/config.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#if !defined(HAMON_USE_STD_CONCEPTS)
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/swappable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/is_object.hpp>
#endif

namespace hamon
{

// 18.6 Object concepts	[concepts.object]

#if defined(HAMON_USE_STD_CONCEPTS)

using std::movable;

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept movable =
	hamon::is_object<T>::value &&
	hamon::move_constructible<T> &&
	hamon::assignable_from<T&, T> &&
	hamon::swappable<T>;

#else

namespace detail
{

template <typename T>
struct movable_impl
{
private:
	template <typename U>
	static auto test(int) -> hamon::conjunction<
		hamon::is_object<U>,
		hamon::move_constructible<U>,
		hamon::assignable_from<U&, U>,
		hamon::swappable<U>>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using movable = typename detail::movable_impl<T>::type;

#endif

template <typename T>
using movable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::movable<T>>;
#else
	hamon::movable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVABLE_HPP
