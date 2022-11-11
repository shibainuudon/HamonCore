/**
 *	@file	tuple_init_type.hpp
 *
 *	@brief	tuple_init_type の定義
 */

#ifndef HAMON_TUPLE_TUPLE_INIT_TYPE_HPP
#define HAMON_TUPLE_TUPLE_INIT_TYPE_HPP

#include <hamon/tuple/detail/tuple_init_type_impl.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{

/**
 *	@brief	最終要素を除いたTupleを返す
 */
template <typename Tuple>
struct tuple_init_type
	: public detail::tuple_init_type_impl<
		hamon::remove_cv_t<Tuple>>
{};

// テンプレートエイリアス
template <typename Tuple>
using tuple_init_type_t = typename tuple_init_type<Tuple>::type;

}	// namespace hamon

#endif // HAMON_TUPLE_TUPLE_INIT_TYPE_HPP
