/**
 *	@file	vector_cat.hpp
 *
 *	@brief	vector_cat の定義
 */

#ifndef HAMON_QVM_VECTOR_VECTOR_CAT_HPP
#define HAMON_QVM_VECTOR_VECTOR_CAT_HPP

#include <hamon/qvm/vector/vector_fwd.hpp>
#include <hamon/qvm/detail/vector_element.hpp>
#include <hamon/qvm/detail/vector_size.hpp>
#include <hamon/type_traits/accumulation.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename... Types>
struct vector_cat_result
{
	using type = hamon::qvm::vector<
		hamon::common_type_t<vector_element_t<Types>...>,
		hamon::accumulation<vector_size<Types>...>::value>;
};

template <typename... Types>
using vector_cat_result_t = typename vector_cat_result<Types...>::type;

template <typename Vec, std::size_t... Is>
HAMON_CONSTEXPR vector_cat_result_t<Vec>
vector_cat_impl_1(
	Vec const& v,
	hamon::index_sequence<Is...>)
{
	return vector_cat_result_t<Vec>{ v[Is]... };
}

template <typename Vec>
HAMON_CONSTEXPR vector_cat_result_t<Vec>
vector_cat_impl(Vec const& v)
{
	return vector_cat_impl_1(
		v,
		hamon::make_index_sequence<vector_size<Vec>::value>{});
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

template <typename Vec1, typename Vec2>
HAMON_CONSTEXPR vector_cat_result_t<Vec1, Vec2>
vector_cat_impl(Vec1 const& v1, Vec2 const& v2)
{
	return vector_cat_impl_2(
		v1,
		v2,
		hamon::make_index_sequence<vector_size<Vec1>::value>{},
		hamon::make_index_sequence<vector_size<Vec2>::value>{});
}

template <typename Vec1, typename Vec2, typename... Args>
HAMON_CONSTEXPR vector_cat_result_t<Vec1, Vec2, Args...>
vector_cat_impl(Vec1 const& v1, Vec2 const& v2, Args const&... args)
{
	return vector_cat_impl(vector_cat_impl(v1, v2), args...);
}

}	// namespace detail

template <typename... Args>
HAMON_CONSTEXPR detail::vector_cat_result_t<Args...>
vector_cat(Args const&... args)
{
	return detail::vector_cat_impl(args...);
}

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_VECTOR_CAT_HPP
