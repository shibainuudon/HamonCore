/**
 *	@file	has_adl_almost_equal.hpp
 *
 *	@brief	has_adl_almost_equal の定義
 */

#ifndef HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ALMOST_EQUAL_HPP
#define HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ALMOST_EQUAL_HPP

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/detail/can_reference.hpp>
#include <type_traits>
#include <utility>

namespace hamon
{

namespace ranges
{

namespace almost_equal_detail
{

#if 0
void almost_equal(const auto&, const auto&) = delete;
#else
template <typename T1, typename T2> void almost_equal(T1 const&, T2 const&) = delete;
#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T1, typename T2>
concept has_adl_almost_equal =
	(hamon::detail::class_or_enum<T1> ||
	 hamon::detail::class_or_enum<T2> ) &&
	requires(T1 const& x, T2 const& y)
	{
		{ almost_equal(x, y) } -> hamon::detail::can_reference;
	};

#else

template <typename T1, typename T2>
struct has_adl_almost_equal_impl
{
private:
	template <typename U1, typename U2,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<U1>::value ||
			hamon::detail::class_or_enum<U2>::value
		>,
		typename S = decltype(almost_equal(std::declval<U1 const&>(), std::declval<U2 const&>()))
	>
	static auto test(int) -> hamon::detail::can_reference<S>;

	template <typename U1, typename U2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T1, T2>(0));
};

template <typename T1, typename T2>
using has_adl_almost_equal = typename has_adl_almost_equal_impl<T1, T2>::type;

#endif

}	// namespace almost_equal_detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CMATH_RANGES_DETAIL_HAS_ADL_ALMOST_EQUAL_HPP
