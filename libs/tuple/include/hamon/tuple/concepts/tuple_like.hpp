/**
 *	@file	tuple_like.hpp
 *
 *	@brief	tuple_like
 */

#ifndef HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
#define HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP

#include <hamon/tuple/concepts/has_tuple_element.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

namespace detail
{

template <typename T, std::size_t... N>
constexpr bool has_tuple_element_all(hamon::index_sequence<N...>)
{
	return (has_tuple_element<T, N> && ...);
}

}	// namespace detail

template <typename T>
concept tuple_like =
	!std::is_reference<T>::value &&
	requires(T t)
	{
		typename std::tuple_size<T>::type;
		requires hamon::derived_from<
			std::tuple_size<T>,
			std::integral_constant<std::size_t, std::tuple_size<T>::value>
		>;
	} &&
	detail::has_tuple_element_all<T>(
		hamon::make_index_sequence<std::tuple_size<T>::value>{});

#else

template <typename T>
struct tuple_like_impl
{
private:
	template <typename U, std::size_t... N>
	static auto test_helper(hamon::index_sequence<N...>)
		-> hamon::conjunction<has_tuple_element<U, N>...>;

	template <typename U,
		typename = typename std::tuple_size<U>::type,
		typename = hamon::enable_if_t<
			hamon::derived_from_t<
				std::tuple_size<U>,
				std::integral_constant<std::size_t, std::tuple_size<U>::value>
			>::value
		>,
		typename Seq = hamon::make_index_sequence<std::tuple_size<U>::value>
	>
	static auto test(int) -> decltype(test_helper<U>(Seq{}));
	
	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using tuple_like = typename tuple_like_impl<T>::type;

#endif

template <typename T>
using tuple_like_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::tuple_like<T>>;
#else
	hamon::tuple_like<T>;
#endif

}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_TUPLE_LIKE_HPP
