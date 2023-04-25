/**
 *	@file	exactly_once.hpp
 *
 *	@brief	exactly_once の定義
 */

#ifndef HAMON_TUPLE_DETAIL_EXACTLY_ONCE_HPP
#define HAMON_TUPLE_DETAIL_EXACTLY_ONCE_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon {
namespace tuple_detail {

template <typename T, typename... Types>
struct exactly_once
{
private:
	template <typename U, typename... UTypes>
	struct count_same_type;

	template <typename U>
	struct count_same_type<U>
		: public hamon::integral_constant<hamon::size_t, 0>
	{};

	template <typename U, typename Head, typename... Tail>
	struct count_same_type<U, Head, Tail...>
		: public hamon::integral_constant<hamon::size_t,
			(hamon::is_same<U, Head>::value ? 1 : 0) +
			count_same_type<U, Tail...>::value
		>
	{};

public:
	static const bool value = (count_same_type<T, Types...>::value == 1);
};

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_EXACTLY_ONCE_HPP
