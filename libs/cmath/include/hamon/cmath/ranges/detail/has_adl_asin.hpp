﻿/**
 *	@file	has_adl_asin.hpp
 *
 *	@brief	has_adl_asin の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ASIN_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ASIN_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace asin_detail
{

#if 0
void asin(const auto&) = delete;
#else
template <typename T> void asin(const T&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_asin =
	hamon::detail::class_or_enum<T> &&
	requires(T const& t)
	{
		{ asin(t) } -> hamon::detail::can_reference;
	};

#else

template <typename T>
struct has_adl_asin_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U>::value>,
		typename S = decltype(asin(std::declval<U const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_asin = typename has_adl_asin_impl<T>::type;

#endif

}	// namespace asin_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ASIN_HPP
