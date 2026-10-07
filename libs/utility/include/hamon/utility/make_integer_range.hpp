/**
 *	@file	make_integer_range.hpp
 *
 *	@brief	make_integer_range を定義
 */

#ifndef HAMON_UTILITY_MAKE_INTEGER_RANGE_HPP
#define HAMON_UTILITY_MAKE_INTEGER_RANGE_HPP

#include <hamon/utility/make_integer_sequence.hpp>

namespace hamon
{

namespace detail
{

template <typename T, T N, typename Seq>
struct make_integer_range_impl_2;

template <typename T, T N, T... Is>
struct make_integer_range_impl_2<T, N, hamon::integer_sequence<T, Is...>>
{
	using type = hamon::integer_sequence<T, (N + Is)...>;
};

template <typename T, T N, T M>
struct make_integer_range_impl
{
	static_assert(N <= M, "");

	using type = typename make_integer_range_impl_2<T, N, hamon::make_integer_sequence<T, M - N>>::type;
};

}	// namespace detail

// [N, M) のinteger_sequenceを得る
template <typename T, T N, T M>
using make_integer_range = typename hamon::detail::make_integer_range_impl<T, N, M>::type;

}	// namespace hamon

#endif // HAMON_UTILITY_MAKE_INTEGER_RANGE_HPP
