/**
 *	@file	tuple_last_type.hpp
 *
 *	@brief	tuple_last_type の定義
 */

#ifndef HAMON_TUPLE_TUPLE_LAST_TYPE_HPP
#define HAMON_TUPLE_TUPLE_LAST_TYPE_HPP

#include <hamon/tuple/detail/tuple_last_type_impl.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{

/**
 *	@brief	Tupleの最終要素の型を返す
 */
template <typename Tuple>
struct tuple_last_type
	: public detail::tuple_last_type_impl<
		hamon::remove_cv_t<Tuple>>
{};

// テンプレートエイリアス
template <typename Tuple>
using tuple_last_type_t = typename tuple_last_type<Tuple>::type;

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_LAST_TYPE_HPP
