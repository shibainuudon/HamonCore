/**
 *	@file	has_adl_repeat.hpp
 *
 *	@brief	has_adl_repeat の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_REPEAT_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_REPEAT_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace repeat_detail
{

#if 0
void repeat(const auto&, const auto&, const auto&) = delete;
#else
template <typename T1, typename T2, typename T3> void repeat(T1 const&, T2 const&, T3 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2, typename T3>
concept has_adl_repeat =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ||
	 hamon::detail::class_or_enum<T3>) &&
	requires(T1 const& x, T2 const& y, T3 const& z)
	{
		{ repeat(x, y, z) } -> hamon::detail::can_reference;
	};

#else

template <typename T1, typename T2, typename T3>
struct has_adl_repeat_impl
{
private:
	template <typename U1, typename U2, typename U3,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1>::value ||
			hamon::detail::class_or_enum<U2>::value ||
			hamon::detail::class_or_enum<U3>::value
		>,
		typename S = decltype(repeat(
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
using has_adl_repeat = typename has_adl_repeat_impl<T1, T2, T3>::type;

#endif

}	// namespace repeat_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_REPEAT_HPP
