/**
 *	@file	tuple_tail.hpp
 *
 *	@brief	tuple_tail の定義
 */

#ifndef HAMON_TUPLE_TUPLE_TAIL_HPP
#define HAMON_TUPLE_TUPLE_TAIL_HPP

#include <hamon/tuple/tuple_size.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/concepts/detail/is_specialization_of_tuple.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename Tuple>
struct tuple_tail_result
{
	using type = Tuple;
};

template <template <typename...> class Tuple, typename Head, typename... Tail>
struct tuple_tail_result<Tuple<Head, Tail...>>
{
	using type = Tuple<Tail...>;
};

template <typename Tuple>
using tuple_tail_result_t = typename tuple_tail_result<hamon::remove_cvref_t<Tuple>>::type;

template <typename Tuple, hamon::size_t... Is>
HAMON_CXX11_CONSTEXPR tuple_tail_result_t<Tuple>
tuple_tail_impl(Tuple&& t, hamon::index_sequence<0, Is...>)
{
	return tuple_tail_result_t<Tuple>{hamon::adl_get<Is>(hamon::forward<Tuple>(t))...};
}

template <typename Tuple>
HAMON_CXX11_CONSTEXPR tuple_tail_result_t<Tuple>
tuple_tail_impl(Tuple&&, hamon::index_sequence<>)
{
	return {};
}

}	// namespace detail

/**
 *	@brief	先頭要素を除いたTupleを返す
 */
template <typename Tuple,
	typename = hamon::enable_if_t<
		hamon::detail::is_specialization_of_tuple<hamon::remove_cvref_t<Tuple>>::value
	>
>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
tuple_tail(Tuple&& t)
{
	return hamon::detail::tuple_tail_impl(
		hamon::forward<Tuple>(t),
		hamon::make_index_sequence<hamon::tuple_size_v<hamon::remove_cvref_t<Tuple>>>{});
}

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_TAIL_HPP
