/**
 *	@file	make_derived_dimension.hpp
 *
 *	@brief	make_derived_dimension の定義
 */

#ifndef HAMON_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP
#define HAMON_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP

#include <hamon/units/detail/derived_dimension.hpp>
#include <hamon/units/detail/dimension_holder.hpp>
#include <hamon/units/detail/base_dimension_traits.hpp>
#include <hamon/tuple/tuple_sort_type.hpp>
#include <hamon/tuple/tuple_filter_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon
{

namespace units
{

/**
 *	@brief	derived_dimensionを作る
 *
 *	demension_holder のリストを受け取って、正規化されたderived_dimensionを返す。
 *	正規化で行う処理は
 *	・基本次元が同じものはまとめる。その際にpowerを加算する。
 *	・powerが0のものは除く
 *	・基本次元をbase_dimension_traits::orderに基いて並び替える
 */
template <typename... DimensionHolders>
struct make_derived_dimension;

/**
 *	@brief	make_derived_dimension::type のエイリアステンプレート
 */
template <typename... DimensionHolders>
using make_derived_dimension_t =
	typename make_derived_dimension<DimensionHolders...>::type;

namespace detail
{

// append_dimension_impl
template <typename Head, typename Tail, typename DimensionHolder>
struct append_dimension_impl;

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename Middle,
	typename... Tails,
	typename DimensionHolder
>
struct append_dimension_impl<
	Tuple<Heads...>,
	Tuple<Middle, Tails...>,
	DimensionHolder>
{
	using type =
		hamon::conditional_t<
			// Middle::type と DimensionHolder::type が同じ型なら
			hamon::is_same<
				typename Middle::type,
				typename DimensionHolder::type
			>::value,
			// Middle::power に DimensionHolder::power を加算した型を返す
			Tuple<
				Heads...,
				dimension_holder<
					typename Middle::type,
					Middle::power + DimensionHolder::power>,
				Tails...
			>,
			// そうでなければ、次の要素へ
			typename append_dimension_impl<
				Tuple<Heads..., Middle>,
				Tuple<Tails...>,
				DimensionHolder
			>::type
		>;
};

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename DimensionHolder
>
struct append_dimension_impl<Tuple<Heads...>, Tuple<>, DimensionHolder>
{
	// 同じ型の要素がみつからなければ、末尾に追加
	using type = Tuple<Heads..., DimensionHolder>;
};

// append_dimension
template <
	typename Tuple,
	typename DimensionHolder>
struct append_dimension;

template <
	template <typename...> class Tuple,
	typename... Types,
	typename DimensionHolder>
struct append_dimension<Tuple<Types...>, DimensionHolder>
	: public append_dimension_impl<Tuple<>, Tuple<Types...>, DimensionHolder>
{};

// power_not_equal_zero
struct power_not_equal_zero
{
	template <typename T>
	using type = hamon::bool_constant<T::power != 0>;
};

// dimension_order_less
struct dimension_order_less
{
	template <typename T1, typename T2>
	using type = hamon::bool_constant<(
		base_dimension_traits<typename T1::type>::order <
		base_dimension_traits<typename T2::type>::order
	)>;
};

// make_derived_dimension_impl
template <typename Dst, typename Src>
struct make_derived_dimension_impl;

template <
	template <typename...> class Tuple,
	typename... Heads,
	typename Middle,
	typename... Tails
>
struct make_derived_dimension_impl<Tuple<Heads...>, Tuple<Middle, Tails...>>
{
	// 再帰的にappend_dimensionを適用する
	using type = typename make_derived_dimension_impl<
		typename append_dimension<Tuple<Heads...>, Middle>::type,
		Tuple<Tails...>
	>::type;
};

template <
	template <typename...> class Tuple,
	typename... Heads
>
struct make_derived_dimension_impl<Tuple<Heads...>, Tuple<>>
{
private:
	// powerが0の要素を削除して、
	using without_power_zero =
		hamon::tuple_filter_type_t<
			Tuple<Heads...>,
			power_not_equal_zero
		>;
public:
	// orderによってソートする
	using type = hamon::tuple_sort_type_t<
		without_power_zero,
		dimension_order_less
	>;
};

}	// namespace detail

template <typename... DimensionHolders>
struct make_derived_dimension
	: public detail::make_derived_dimension_impl<
		derived_dimension<>, derived_dimension<DimensionHolders...>>
{};

}	// namespace units

}	// namespace hamon

#endif // HAMON_UNITS_DETAIL_MAKE_DERIVED_DIMENSION_HPP
