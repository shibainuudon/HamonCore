/**
 *	@file	tuple_for_each.hpp
 *
 *	@brief	tuple_for_each の定義
 */

#ifndef HAMON_RANGES_DETAIL_TUPLE_FOR_EACH_HPP
#define HAMON_RANGES_DETAIL_TUPLE_FOR_EACH_HPP

#include <hamon/functional/invoke.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {
namespace detail {

template <typename... Types>
HAMON_CXX14_CONSTEXPR void swallow(Types...) HAMON_NOEXCEPT {}

template <typename F>
struct tuple_for_each_fn
{
	F& m_f;

	template <typename... Ts>
	HAMON_CXX14_CONSTEXPR auto operator()(Ts&&... elements) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		swallow((hamon::invoke(m_f, hamon::forward<Ts>(elements)), 0)...))
};

template <typename F, typename Tuple>
HAMON_CXX14_CONSTEXPR auto tuple_for_each(F&& f, Tuple&& t)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	hamon::apply(tuple_for_each_fn<F>{f}, hamon::forward<Tuple>(t)))

template <typename F, typename Tuple1, typename Tuple2, hamon::size_t... I>
HAMON_CXX14_CONSTEXPR auto
tuple_for_each2_impl(F&& f, Tuple1&& t1, Tuple2&& t2, hamon::index_sequence<I...>)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	swallow((hamon::invoke(
		hamon::forward<F>(f),
		hamon::adl_get<I>(hamon::forward<Tuple1>(t1)),
		hamon::adl_get<I>(hamon::forward<Tuple2>(t2))), 0)...))

template <typename F, typename Tuple1, typename Tuple2>
HAMON_CXX14_CONSTEXPR auto
tuple_for_each2(F&& f, Tuple1&& t1, Tuple2&& t2)
HAMON_NOEXCEPT_DECLTYPE_RETURN(
	tuple_for_each2_impl(
		hamon::forward<F>(f),
		hamon::forward<Tuple1>(t1),
		hamon::forward<Tuple2>(t2),
		hamon::make_index_sequence<hamon::tuple_size<hamon::remove_reference_t<Tuple1>>::value>{}))

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif // HAMON_RANGES_DETAIL_tuple_for_each_HPP
