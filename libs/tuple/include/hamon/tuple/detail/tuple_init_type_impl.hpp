/**
 *	@file	tuple_init_type_impl.hpp
 *
 *	@brief	tuple_init_type_impl の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_INIT_TYPE_IMPL_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_INIT_TYPE_IMPL_HPP

#include <hamon/type_traits/nth.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <cstddef>

namespace hamon
{

namespace detail
{

// tuple_init_type_impl_2
template <typename Tuple, typename Indices>
struct tuple_init_type_impl_2;

template <
	template <typename...> class Tuple,
	typename... Types,
	std::size_t... Indices>
struct tuple_init_type_impl_2<
	Tuple<Types...>,
	hamon::index_sequence<Indices...>>
{
	using type =
		Tuple<hamon::nth_t<Indices, Types...>...>;
};

// tuple_init_type_impl_1
template <typename Tuple, std::size_t N>
struct tuple_init_type_impl_1
	: public tuple_init_type_impl_2<
		Tuple, hamon::make_index_sequence<N - 1>
	>
{};

template <typename Tuple>
struct tuple_init_type_impl_1<Tuple, 0>
{
	using type = Tuple;
};

// tuple_init_type_impl
template <typename Tuple>
struct tuple_init_type_impl;

template <
	template <typename...> class Tuple,
	typename... Types
>
struct tuple_init_type_impl<Tuple<Types...>>
	: public detail::tuple_init_type_impl_1<
		Tuple<Types...>, sizeof...(Types)
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_INIT_TYPE_IMPL_HPP
