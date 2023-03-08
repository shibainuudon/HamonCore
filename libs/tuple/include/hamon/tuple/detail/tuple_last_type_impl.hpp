/**
 *	@file	tuple_last_type_impl.hpp
 *
 *	@brief	tuple_last_type_impl の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_LAST_TYPE_IMPL_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_LAST_TYPE_IMPL_HPP

#include <hamon/type_traits/nth.hpp>

namespace hamon
{

namespace detail
{

// tuple_last_type_impl
template <typename Tuple>
struct tuple_last_type_impl;

template <
	template <typename...> class Tuple,
	typename... Types>
struct tuple_last_type_impl<Tuple<Types...>>
{
	using type =
		hamon::nth_t<sizeof...(Types) - 1, Types...>;
};

template <
	template <typename...> class Tuple
>
struct tuple_last_type_impl<Tuple<>>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_LAST_TYPE_IMPL_HPP
