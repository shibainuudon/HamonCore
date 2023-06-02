/**
 *	@file	cpp17_hash.hpp
 *
 *	@brief	cpp17_hash の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_CPP17_HASH_HPP
#define HAMON_CONCEPTS_DETAIL_CPP17_HASH_HPP

#include <hamon/concepts/detail/cpp17_function_object.hpp>
#include <hamon/concepts/detail/cpp17_copy_constructible.hpp>
#include <hamon/concepts/detail/cpp17_destructible.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename Key>
concept cpp17_hash =
	hamon::detail::cpp17_function_object<T, Key> &&
	hamon::detail::cpp17_copy_constructible<T> &&
	hamon::detail::cpp17_destructible<T> &&
	requires(T h, Key k, Key& u)
	{
		{ h(k) } -> hamon::same_as<std::size_t>;
		{ h(u) } -> hamon::same_as<std::size_t>;
	};

#else

template <typename T, typename Key>
struct cpp17_hash_impl
{
private:
	template <typename U, typename UKey,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::detail::cpp17_function_object<U, UKey>,
			hamon::detail::cpp17_copy_constructible<U>,
			hamon::detail::cpp17_destructible<U>
		>::value>,
		typename R1 = decltype(hamon::declval<U>()(hamon::declval<UKey>())),
		typename R2 = decltype(hamon::declval<U>()(hamon::declval<UKey&>()))
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as<R1, std::size_t>,
		hamon::same_as<R2, std::size_t>
	>;

	template <typename U, typename UKey>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, Key>(0));
};

template <typename T, typename Key>
using cpp17_hash =
	typename cpp17_hash_impl<T, Key>::type;

#endif

template <typename T, typename Key>
using cpp17_hash_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::detail::cpp17_hash<T, Key>>;
#else
	hamon::detail::cpp17_hash<T, Key>;
#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_CPP17_HASH_HPP
