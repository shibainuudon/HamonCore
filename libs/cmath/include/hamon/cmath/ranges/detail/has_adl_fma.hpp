﻿/**
 *	@file	has_adl_fma.hpp
 *
 *	@brief	has_adl_fma の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMA_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMA_HPP

#include <hamon/cmath/ranges/detail/is_not_void.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace ranges
{

namespace fma_detail
{

#if 0
void fma(const auto&, const auto&, const auto&) = delete;
#else
template <typename T1, typename T2, typename T3> void fma(T1 const&, T2 const&, T3 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2, typename T3>
concept has_adl_fma =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ||
	 hamon::detail::class_or_enum<T3>) &&
	requires(T1 const& x, T2 const& y, T3 const& z)
	{
		{ fma(x, y, z) } -> hamon::detail::is_not_void;
	};

#else

template <typename T1, typename T2, typename T3>
struct has_adl_fma_impl
{
private:
	template <typename U1, typename U2, typename U3,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1>::value ||
			hamon::detail::class_or_enum<U2>::value ||
			hamon::detail::class_or_enum<U3>::value
		>,
		typename S = decltype(fma(
			hamon::declval<U1 const&>(),
			hamon::declval<U2 const&>(),
			hamon::declval<U3 const&>()))
	>
	static auto test(int) -> hamon::detail::is_not_void<S>;

	template <typename U1, typename U2, typename U3>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T1, T2, T3>(0));
};

template <typename T1, typename T2, typename T3>
using has_adl_fma = typename has_adl_fma_impl<T1, T2, T3>::type;

#endif

}	// namespace fma_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_FMA_HPP
