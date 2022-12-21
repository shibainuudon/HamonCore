﻿/**
 *	@file	has_adl_trunc.hpp
 *
 *	@brief	has_adl_trunc の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_TRUNC_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_TRUNC_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace trunc_detail
{

#if 0
void trunc(const auto&) = delete;
#else
template <typename T> void trunc(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_trunc =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ trunc(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_trunc_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(trunc(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_trunc = typename has_adl_trunc_impl<T>::type;

#endif

}	// namespace trunc_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_TRUNC_HPP
