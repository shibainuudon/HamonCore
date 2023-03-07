/**
 *	@file	nth.hpp
 *
 *	@brief	nth の定義
 */

#ifndef HAMON_TYPE_TRAITS_NTH_HPP
#define HAMON_TYPE_TRAITS_NTH_HPP

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

/**
 *	@brief		テンプレートパラメータパックのN番目の型を得る
 *
 *	@tparam		N
 *	@tparam		Types
 */
template <hamon::size_t N, typename... Types>
struct nth;

/**
 *	@brief	nthのエイリアステンプレート
 */
template <hamon::size_t N, typename... Types>
using nth_t = typename nth<N, Types...>::type;

}	// namespace hamon

#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/index_sequence.hpp>
#include <hamon/utility/index_sequence_for.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

// 単純な再帰での実装
// 再帰深度はO(N)
#if 0
template <typename Head, typename... Tail>
struct nth<0, Head, Tail...>
{
	using type = Head;
};

template <hamon::size_t N, typename Head, typename... Tail>
struct nth<N, Head, Tail...>
	: public nth<N - 1, Tail...>
{};
#endif

// "void* trick" を使った実装。
// 再帰深度はO(logN)
#if 0
namespace nth_detail
{

template <typename Seq>
struct nth_impl;

template <hamon::size_t... Indices>
struct nth_impl<hamon::index_sequence<Indices...>>
{
	template <hamon::size_t>
	struct void_ptr
	{
		using type = void*;
	};

	template <typename T>
	static T eval(typename void_ptr<Indices>::type..., T*, ...);
};

}	// namespace nth_detail

template <hamon::size_t I, typename... Types>
struct nth
{
private:
	using Seq = hamon::make_index_sequence<I>;

	// MSVC12 で decltype()::type ができないので、一時的な型で受ける
	using tmp_type = decltype(
		nth_detail::nth_impl<Seq>::eval(
			static_cast<hamon::type_identity<Types>*>(nullptr)...));
public:
	using type = typename tmp_type::type;
};
#endif

// 多重継承を使った実装
// 再帰深度はO(logN)
#if 1
namespace nth_detail
{

template <hamon::size_t N, typename T>
struct element_holder
	: public hamon::type_identity<T>
{};

template <typename Sequence, typename... Types>
struct type_tuple;

template <hamon::size_t... Indices, typename... Types>
struct type_tuple<hamon::index_sequence<Indices...>, Types...>
	: public element_holder<Indices, Types>...
{};

template <hamon::size_t N, typename T>
static element_holder<N, T> select(element_holder<N, T>);

template <bool, hamon::size_t N, typename... Types>
struct nth
{
private:
	using Seq = hamon::index_sequence_for<Types...>;
	using Tmp = decltype(select<N>(
		hamon::declval<type_tuple<Seq, Types...>>()));
public:
	using type = typename Tmp::type;
};

template <hamon::size_t N, typename... Types>
struct nth<false, N, Types...>
{};

}	// namespace nth_detail

template <hamon::size_t N, typename... Types>
struct nth : public nth_detail::nth<(N < sizeof...(Types)), N, Types...>
{};
#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_NTH_HPP
