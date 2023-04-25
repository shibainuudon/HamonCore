/**
 *	@file	find_index.hpp
 *
 *	@brief	find_index の定義
 */

#ifndef HAMON_TUPLE_DETAIL_FIND_INDEX_HPP
#define HAMON_TUPLE_DETAIL_FIND_INDEX_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon {
namespace tuple_detail {

template <typename T, typename... Types>
struct find_index
{
private:
	template <hamon::size_t I, typename U, typename... UTypes>
	struct find_index_impl;

	template <hamon::size_t I, typename U>
	struct find_index_impl<I, U>
	{
		static const hamon::size_t value = static_cast<hamon::size_t>(-1);
	};

	template <hamon::size_t I, typename U, typename Head, typename... Tail>
	struct find_index_impl<I, U, Head, Tail...>
	{
		static const hamon::size_t value =
			hamon::is_same<U, Head>::value ?
			I :
			find_index_impl<I+1, U, Tail...>::value;
	};

public:
	static const hamon::size_t value =
		find_index_impl<0, T, Types...>::value;
};

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_FIND_INDEX_HPP
