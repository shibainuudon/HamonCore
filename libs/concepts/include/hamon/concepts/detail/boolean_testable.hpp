/**
 *	@file	boolean_testable.hpp
 *
 *	@brief	boolean_testable の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP
#define HAMON_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept boolean_testable_impl = hamon::convertible_to<T, bool>;

template <typename T>
concept boolean_testable =
	boolean_testable_impl<T> &&
	requires(T&& t)
	{
		{ !std::forward<T>(t) } -> boolean_testable_impl;
	};

#else

template <typename T>
struct boolean_testable_impl
{
private:
	template <typename U,
		typename V = decltype(!std::declval<U&&>())
	>
	static auto test(int) -> hamon::conjunction<
		hamon::convertible_to<U, bool>,
		hamon::convertible_to<V, bool>
	>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using boolean_testable = typename boolean_testable_impl<T>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_BOOLEAN_TESTABLE_HPP
