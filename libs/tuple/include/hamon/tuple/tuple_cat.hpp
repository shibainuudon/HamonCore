/**
 *	@file	tuple_cat.hpp
 *
 *	@brief	tuple_cat の定義
 */

#ifndef HAMON_TUPLE_TUPLE_CAT_HPP
#define HAMON_TUPLE_TUPLE_CAT_HPP

#include <hamon/tuple/config.hpp>

#if defined(HAMON_USE_STD_TUPLE)

namespace hamon
{

using std::tuple_cat;

}	// namespace hamon

#else

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/tuple/adl_get.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace tuple_detail
{

template <typename R, typename... Tuples>
struct tuple_cat_result;

template <typename... Elems, typename T, typename... Tuples>
struct tuple_cat_result<hamon::tuple<Elems...>, T, Tuples...>
{
private:
	using U = hamon::remove_cvref_t<T>;	// [tuple.creation]/7.2
	using S = std::tuple_size<U>;		// [tuple.creation]/7.4

	template <typename>
	struct impl;

	template <hamon::size_t... K>
	struct impl<hamon::index_sequence<K...>>
	{
		using type = hamon::tuple<
			Elems...,
			hamon::tuple_element_t<K, U>...	// [tuple.creation]/7.5
		>;
	};

	using tmp = typename impl<
		hamon::make_index_sequence<S::value>
	>::type;

public:
	using type = typename tuple_cat_result<tmp, Tuples...>::type;
};

template <typename... Elems>
struct tuple_cat_result<hamon::tuple<Elems...>>
{
	using type = hamon::tuple<Elems...>;
};

template <typename... Tuples>
using tuple_cat_result_t =
	typename tuple_cat_result<hamon::tuple<>, Tuples...>::type;

template <typename R, typename... Tuples>
struct tuple_cat_impl;

template <typename R, typename T, typename... Tuples>
struct tuple_cat_impl<R, T, Tuples...>
{
private:
	template <hamon::size_t... K, typename... CTypes>
	static HAMON_CXX11_CONSTEXPR R
	impl(hamon::index_sequence<K...>, T&& tp, Tuples&&... tpls, CTypes&&... celems)
	{
		return tuple_cat_impl<R, Tuples...>::invoke(
			hamon::forward<Tuples>(tpls)...,
			hamon::forward<CTypes>(celems)...,
			hamon::adl_get<K>(hamon::forward<T>(tp))...);		// [tuple.creation]/7.6
	}

public:
	template <typename... CTypes>
	static HAMON_CXX11_CONSTEXPR R
	invoke(T&& tp, Tuples&&... tpls, CTypes&&... celems)
	{
		using U = hamon::remove_reference_t<T>;
		return impl(
			hamon::make_index_sequence<std::tuple_size<U>::value>{},
			hamon::forward<T>(tp),
			hamon::forward<Tuples>(tpls)...,
			hamon::forward<CTypes>(celems)...);
	}
};

template <typename R>
struct tuple_cat_impl<R>
{
	template <typename... CTypes>
	static HAMON_CXX11_CONSTEXPR R
	invoke(CTypes&&... celems)
	{
		return R(hamon::forward<CTypes>(celems)...);	// [tuple.creation]/9
	}
};

}	// namespace tuple_detail

// Tuple creation functions	[tuple.creation]

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::tuple_like... Tuples
#else
	typename... Tuples,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::tuple_like<Tuples>...
	>::value>
#endif
>
inline HAMON_CXX11_CONSTEXPR auto
tuple_cat(Tuples&&... tpls)
-> tuple_detail::tuple_cat_result_t<Tuples...>
{
	using R = tuple_detail::tuple_cat_result_t<Tuples...>;
	return tuple_detail::tuple_cat_impl<R, Tuples...>::invoke(
		hamon::forward<Tuples>(tpls)...);
}

}	// namespace hamon

#endif

#endif // HAMON_TUPLE_TUPLE_CAT_HPP
