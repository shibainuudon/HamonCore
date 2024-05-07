/**
 *	@file	tuple_compare.hpp
 *
 *	@brief	tuple_compare の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_COMPARE_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_COMPARE_HPP

#include <hamon/tuple/adl_get.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/compare/common_comparison_category.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace tuple_detail {

template <hamon::size_t N, hamon::size_t I = 0>
struct tuple_compare
{
	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	equal(T const& t, U const& u)
	{
		return bool(hamon::adl_get<I>(t) == hamon::adl_get<I>(u)) &&
			tuple_compare<N, I + 1>::equal(t, u);
	}

	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	less(T const& t, U const& u)
	{
		return
			  bool(hamon::adl_get<I>(t) < hamon::adl_get<I>(u)) ||
			(!bool(hamon::adl_get<I>(u) < hamon::adl_get<I>(t)) &&
			tuple_compare<N, I + 1>::less(t, u));
	}

	template <typename Result, typename T, typename U>
	static HAMON_CXX14_CONSTEXPR Result
	three_way(T const& t, U const& u)
	{
		auto c = hamon::detail::synth_three_way(hamon::adl_get<I>(t), hamon::adl_get<I>(u));
		if (c != 0)
		{
			return c;
		}
		return tuple_compare<N, I + 1>::template three_way<Result>(t, u);
	}
};

template <hamon::size_t N>
struct tuple_compare<N, N>
{
	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	equal(T const&, U const&)
	{
		return true;
	}

	template <typename T, typename U>
	static HAMON_CXX11_CONSTEXPR bool
	less(T const&, U const&)
	{
		return false;
	}

	template <typename Result, typename T, typename U>
	static HAMON_CXX14_CONSTEXPR Result
	three_way(T const&, U const&)
	{
		return hamon::strong_ordering::equal;
	}
};

template <typename... TTypes, typename UTuple>
inline HAMON_CXX11_CONSTEXPR bool
tuple_eq(tuple<TTypes...> const& t, UTuple const& u)
{
	static_assert(sizeof...(TTypes) == std::tuple_size<UTuple>::value, "[tuple.rel]/2");
	return tuple_detail::tuple_compare<sizeof...(TTypes)>::equal(t, u);
}

template <typename TTuple, typename UTuple>
inline HAMON_CXX11_CONSTEXPR bool
tuple_less(TTuple const& t, UTuple const& u)
{
	static_assert(std::tuple_size<TTuple>::value == std::tuple_size<UTuple>::value, "");
	return tuple_detail::tuple_compare<std::tuple_size<TTuple>::value>::less(t, u);
}

template <typename... TTypes, typename UTuple, hamon::size_t... Is,
	typename Result = hamon::common_comparison_category_t<
		hamon::detail::synth_three_way_result<TTypes, hamon::tuple_element_t<Is, UTuple>>...
	>
>
inline HAMON_CXX11_CONSTEXPR Result
tuple_3way_impl(tuple<TTypes...> const& t, UTuple const& u, hamon::index_sequence<Is...>)
{
	return tuple_detail::tuple_compare<sizeof...(TTypes)>::template three_way<Result>(t, u);
}

template <typename... TTypes, typename UTuple>
inline HAMON_CXX11_CONSTEXPR auto
tuple_3way(tuple<TTypes...> const& t, UTuple const& u)
->decltype(tuple_3way_impl(t, u, hamon::make_index_sequence<std::tuple_size<UTuple>::value>{}))
{
	return tuple_3way_impl(t, u, hamon::make_index_sequence<std::tuple_size<UTuple>::value>{});
}

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_COMPARE_HPP
