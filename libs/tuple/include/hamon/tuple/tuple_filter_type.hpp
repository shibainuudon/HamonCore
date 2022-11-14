/**
 *	@file	tuple_filter_type.hpp
 *
 *	@brief	tuple_filter_type の定義
 */

#ifndef HAMON_TUPLE_TUPLE_FILTER_TYPE_HPP
#define HAMON_TUPLE_TUPLE_FILTER_TYPE_HPP

#include <hamon/tuple/detail/tuple_filter_type_impl.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{

/**
 *	@brief	Tupleの要素のうち、条件Predを満たす要素だけが要素となるTuple型を取得する
 */
template <typename Tuple, typename Pred>
struct tuple_filter_type
	: public detail::tuple_filter_type_impl<
		hamon::remove_cv_t<Tuple>, Pred> {};

// テンプレートエイリアス
template <typename Tuple, typename Pred>
using tuple_filter_type_t = typename tuple_filter_type<Tuple, Pred>::type;

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_FILTER_TYPE_HPP
