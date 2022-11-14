/**
 *	@file	tuple_filter_type_impl.hpp
 *
 *	@brief	tuple_filter_type_impl の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_FILTER_TYPE_IMPL_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_FILTER_TYPE_IMPL_HPP

#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

namespace detail
{

// tuple_filter_type_impl_1
template <typename Dst, typename Src, typename Pred>
struct tuple_filter_type_impl_1;

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename Middle,
	typename... Tails,
	typename Pred
>
struct tuple_filter_type_impl_1<Tuple<Heads...>, Tuple<Middle, Tails...>, Pred>
{
	using type = typename tuple_filter_type_impl_1<
		hamon::conditional_t<
			(Pred::template type<Middle>::value),
			Tuple<Heads..., Middle>,
			Tuple<Heads...>
		>,
		Tuple<Tails...>,
		Pred
	>::type;
};

template <
	template <typename...> class Tuple,
	typename... Types,
	typename Pred
>
struct tuple_filter_type_impl_1<Tuple<Types...>, Tuple<>, Pred>
{
	using type = Tuple<Types...>;
};

// tuple_filter_type_impl
template <typename Tuple, typename Pred>
struct tuple_filter_type_impl;

template <
	template <typename...> class Tuple,
	typename... Types,
	typename Pred
>
struct tuple_filter_type_impl<Tuple<Types...>, Pred>
	: public detail::tuple_filter_type_impl_1<
		Tuple<>,
		Tuple<Types...>,
		Pred
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_FILTER_TYPE_IMPL_HPP
