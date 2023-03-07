/**
 *	@file	op_eq_lt.hpp
 *
 *	@brief	op_eq_lt の定義
 */

#ifndef HAMON_COMPARE_DETAIL_OP_EQ_LT_HPP
#define HAMON_COMPARE_DETAIL_OP_EQ_LT_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if 0//defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept op_eq_lt = requires(T&& t, U&& u)
{
	{ static_cast<T&&>(t) == static_cast<U&&>(u) } -> hamon::convertible_to<bool>;
	{ static_cast<T&&>(t) <  static_cast<U&&>(u) } -> hamon::convertible_to<bool>;
};

#else

template <typename T, typename U>
struct op_eq_lt_impl
{
private:
	template <typename T2, typename U2,
		typename R1 = decltype(hamon::declval<T2&&>() == hamon::declval<U2&&>()),
		typename R2 = decltype(hamon::declval<T2&&>() <  hamon::declval<U2&&>())
	>
	static auto test(int) -> hamon::conjunction<
		hamon::convertible_to_t<R1, bool>,
		hamon::convertible_to_t<R2, bool>
	>;

	template <typename T2, typename U2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, U>(0));
};

template <typename T, typename U>
using op_eq_lt =
	typename op_eq_lt_impl<T, U>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_COMPARE_DETAIL_OP_EQ_LT_HPP
