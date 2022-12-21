/**
 *	@file	has_adl_lerp.hpp
 *
 *	@brief	has_adl_lerp の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LERP_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LERP_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace lerp_detail
{

#if 0
void lerp(const auto&, const auto&, const auto&) = delete;
#else
template <typename T1, typename T2, typename T3> void lerp(T1 const&, T2 const&, T3 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2, typename T3>
concept has_adl_lerp =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ||
	 hamon::detail::class_or_enum<T3>) &&
	requires(T1 const& x, T2 const& y, T3 const& z)
	{
		{ lerp(x, y, z) } -> hamon::detail::can_reference;
	};

#else

template <typename T1, typename T2, typename T3>
struct has_adl_lerp_impl
{
private:
	template <typename U1, typename U2, typename U3,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1>::value ||
			hamon::detail::class_or_enum<U2>::value ||
			hamon::detail::class_or_enum<U3>::value
		>,
		typename S = decltype(lerp(
			std::declval<U1 const&>(),
			std::declval<U2 const&>(),
			std::declval<U3 const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U1, typename U2, typename U3>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T1, T2, T3>(0));
};

template <typename T1, typename T2, typename T3>
using has_adl_lerp = typename has_adl_lerp_impl<T1, T2, T3>::type;

#endif

}	// namespace lerp_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_LERP_HPP
