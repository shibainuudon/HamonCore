/**
 *	@file	has_tuple_element.hpp
 *
 *	@brief	has_tuple_element
 */

#ifndef HAMON_TUPLE_CONCEPTS_HAS_TUPLE_ELEMENT_HPP
#define HAMON_TUPLE_CONCEPTS_HAS_TUPLE_ELEMENT_HPP

#include <hamon/tuple/tuple_element.hpp>
#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <tuple>
#include <utility>

namespace hamon
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, std::size_t N>
concept has_tuple_element =
	requires(T t)
	{
		typename hamon::tuple_element_t<N, hamon::remove_const_t<T>>;
		{ get<N>(t) } -> hamon::convertible_to<hamon::tuple_element_t<N, T> const&>;
	};

#else

template <typename T, std::size_t N>
struct has_tuple_element_impl
{
private:
	template <typename U, std::size_t M,
		typename = hamon::tuple_element_t<M, hamon::remove_const_t<U>>,
		typename B = decltype(std::get<M>(std::declval<U>()))
	>
	static auto test(int) -> hamon::convertible_to_t<B, hamon::tuple_element_t<M, U> const&>;
	
	template <typename U, std::size_t M>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, N>(0));
};

template <typename T, std::size_t N>
using has_tuple_element = typename has_tuple_element_impl<T, N>::type;

#endif

}	// namespace hamon

#endif // HAMON_TUPLE_CONCEPTS_HAS_TUPLE_ELEMENT_HPP
