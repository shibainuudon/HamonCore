/**
 *	@file	vector_cat.hpp
 *
 *	@brief	vector_cat の定義
 */

#ifndef HAMON_QVM_VECTOR_VECTOR_CAT_HPP
#define HAMON_QVM_VECTOR_VECTOR_CAT_HPP

#include <hamon/type_traits/accumulation.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename... Vectors>
struct vector_cat_result;

template <
	template <typename, std::size_t> class Vector,
	typename... Ts, std::size_t... Ns
>
struct vector_cat_result<Vector<Ts, Ns>...>
{
	using type = Vector<
		hamon::common_type_t<Ts...>,
		hamon::accumulation<std::integral_constant<std::size_t, Ns>...>::value>;
};

template <typename... Vectors>
using vector_cat_result_t = typename vector_cat_result<Vectors...>::type;

template <
	template <typename, std::size_t> class Vector,
	typename T, std::size_t N
>
HAMON_CONSTEXPR Vector<T, N>
vector_cat_impl(Vector<T, N> const& v)
{
	return v;
}

template <typename Vec1, typename Vec2, std::size_t... Is, std::size_t... Js>
HAMON_CONSTEXPR vector_cat_result_t<Vec1, Vec2>
vector_cat_impl_2(
	Vec1 const& v1,
	Vec2 const& v2,
	hamon::index_sequence<Is...>,
	hamon::index_sequence<Js...>)
{
	return { v1[Is]..., v2[Js]... };
}

template <
	template <typename, std::size_t> class Vector,
	typename T1, std::size_t N1,
	typename T2, std::size_t N2
>
HAMON_CONSTEXPR vector_cat_result_t<Vector<T1, N1>, Vector<T2, N2>>
vector_cat_impl(Vector<T1, N1> const& v1, Vector<T2, N2> const& v2)
{
	return vector_cat_impl_2(
		v1,
		v2,
		hamon::make_index_sequence<N1>{},
		hamon::make_index_sequence<N2>{});
}

template <typename Vec1, typename Vec2, typename... Args>
HAMON_CONSTEXPR vector_cat_result_t<Vec1, Vec2, Args...>
vector_cat_impl(Vec1 const& v1, Vec2 const& v2, Args const&... args)
{
	return vector_cat_impl(vector_cat_impl(v1, v2), args...);
}

}	// namespace detail

template <typename... Vectors>
HAMON_CONSTEXPR detail::vector_cat_result_t<Vectors...>
vector_cat(Vectors const&... vecs)
{
	return detail::vector_cat_impl(vecs...);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_VECTOR_CAT_HPP
