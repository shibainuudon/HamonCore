/**
 *	@file	tuple_sort_type_impl.hpp
 *
 *	@brief	tuple_sort_type_impl の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_SORT_TYPE_IMPL_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_SORT_TYPE_IMPL_HPP

#include <hamon/tuple/tuple_init_type.hpp>
#include <hamon/tuple/tuple_last_type.hpp>
#include <hamon/type_traits/conditional.hpp>

namespace hamon
{

namespace detail
{

// tuple_sort_type_impl_2
template <typename Head, typename Tail, typename Compare>
struct tuple_sort_type_impl_2;

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename T1,
	typename T2,
	typename... Tails,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<T1, T2, Tails...>, Compare
>
{
	using type =
		hamon::conditional_t<
			//(T1::value < T2::value),
			(Compare::template type<T1, T2>::value),
			typename tuple_sort_type_impl_2<
				Tuple<Heads..., T1>,
				Tuple<T2, Tails...>,
				Compare
			>::type,
			typename tuple_sort_type_impl_2<
				Tuple<Heads..., T2>,
				Tuple<T1, Tails...>,
				Compare
			>::type
		>;
};

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename T,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<T>, Compare
>
{
	using type = Tuple<Heads..., T>;
};

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename Compare
>
struct tuple_sort_type_impl_2<
	Tuple<Heads...>, Tuple<>, Compare
>
{
	using type = Tuple<Heads...>;
};

// tuple_sort_type_impl_1
template <typename Head, typename Tail, typename Compare>
struct tuple_sort_type_impl_1
{
	using type = Tail;
};

template <
	template <typename...> class Tuple,
	typename H1,
	typename... Heads,
	typename... Tails,
	typename Compare
>
struct tuple_sort_type_impl_1<
	Tuple<H1, Heads...>, Tuple<Tails...>, Compare
>
{
	using tmp =
		typename tuple_sort_type_impl_2<
			Tuple<>,
			Tuple<H1, Heads...>,
			Compare
		>::type;

	using type = typename tuple_sort_type_impl_1<
		hamon::tuple_init_type_t<tmp>,
		Tuple<hamon::tuple_last_type_t<tmp>, Tails...>,
		Compare
	>::type;
};

// tuple_sort_type_impl
template <typename Tuple, typename Compare>
struct tuple_sort_type_impl;

template <
	template <typename...> class Tuple,
	typename... Types,
	typename Compare
>
struct tuple_sort_type_impl<Tuple<Types...>, Compare>
	: public detail::tuple_sort_type_impl_1<
		Tuple<Types...>, Tuple<>, Compare
	>
{};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_SORT_TYPE_IMPL_HPP
