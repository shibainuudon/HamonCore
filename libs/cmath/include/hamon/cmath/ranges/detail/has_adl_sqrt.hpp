﻿/**
 *	@file	has_adl_sqrt.hpp
 *
 *	@brief	has_adl_sqrt の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_SQRT_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_SQRT_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace sqrt_detail
{

#if 0
void sqrt(const auto&) = delete;
#else
template <typename T> void sqrt(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_sqrt =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ sqrt(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_sqrt_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(sqrt(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_sqrt = typename has_adl_sqrt_impl<T>::type;

#endif

}	// namespace sqrt_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_SQRT_HPP
