/**
 *	@file	tuple_sort_type.hpp
 *
 *	@brief	tuple_sort_type の定義
 */

#ifndef HAMON_TUPLE_TUPLE_SORT_TYPE_HPP
#define HAMON_TUPLE_TUPLE_SORT_TYPE_HPP

#include <hamon/tuple/detail/tuple_sort_type_impl.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{

/**
 *	@brief	tuple_sort_type でデフォルトで使われる比較演算
 */
struct value_less
{
	template <typename T1, typename T2>
	using type = hamon::bool_constant<(T1::value < T2::value)>;
};

/**
 *	@brief	Tupleの要素をCompareに従って並べ替えたTuple型を取得する
 *
 *	Compareを指定しなかったときは、
 *	Tupleの各要素をTとすると、T::valueが昇順になるように並べ替える。
 */
template <typename Tuple, typename Compare = value_less>
struct tuple_sort_type
	: public detail::tuple_sort_type_impl<
		hamon::remove_cv_t<Tuple>, Compare> {};

// テンプレートエイリアス
template <typename Tuple, typename Compare = value_less>
using tuple_sort_type_t = typename tuple_sort_type<Tuple, Compare>::type;

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_SORT_TYPE_HPP
