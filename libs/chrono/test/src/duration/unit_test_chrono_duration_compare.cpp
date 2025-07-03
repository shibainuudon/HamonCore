/**
 *	@file	unit_test_chrono_duration_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr bool operator==(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr bool operator<(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr bool operator>(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr bool operator<=(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	constexpr bool operator>=(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 *
 *	template<class Rep1, class Period1, class Rep2, class Period2>
 *	requires three_way_comparable<typename CT::rep>
 *	constexpr auto operator<=>(const duration<Rep1, Period1>& lhs, const duration<Rep2, Period2>& rhs);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/compare.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_compare_test
{

GTEST_TEST(DurationTest, CompareTest)
{
	using Duration1 = hamon::chrono::duration<int, hamon::ratio<60>>;
	using Duration2 = hamon::chrono::duration<short, hamon::ratio<1>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() == hamon::declval<Duration2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() != hamon::declval<Duration2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() <  hamon::declval<Duration2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() >  hamon::declval<Duration2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() <= hamon::declval<Duration2>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Duration1>() >= hamon::declval<Duration2>()), bool>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(hamon::declval<Duration1>() == hamon::declval<Duration2>()), "");
	static_assert(noexcept(hamon::declval<Duration1>() != hamon::declval<Duration2>()), "");
	static_assert(noexcept(hamon::declval<Duration1>() <  hamon::declval<Duration2>()), "");
	static_assert(noexcept(hamon::declval<Duration1>() >  hamon::declval<Duration2>()), "");
	static_assert(noexcept(hamon::declval<Duration1>() <= hamon::declval<Duration2>()), "");
	static_assert(noexcept(hamon::declval<Duration1>() >= hamon::declval<Duration2>()), "");
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(noexcept(hamon::declval<Duration1>() <=> hamon::declval<Duration2>()), "");
#endif
#endif

	{
		HAMON_CXX11_CONSTEXPR Duration1 d1{1};
		HAMON_CXX11_CONSTEXPR Duration2 d2{1};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 == d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 != d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 <  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 >  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 <= d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 >= d2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_gt(d1 <=> d2));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR Duration1 d1{1};
		HAMON_CXX11_CONSTEXPR Duration2 d2{60};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 == d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 != d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 <  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 >  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 <= d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 >= d2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_eq(d1 <=> d2));
#endif
	}
	{
		HAMON_CXX11_CONSTEXPR Duration1 d1{1};
		HAMON_CXX11_CONSTEXPR Duration2 d2{61};
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 == d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 != d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 <  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 >  d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (d1 <= d2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(!(d1 >= d2));
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::is_lt(d1 <=> d2));
#endif
	}
}

}	// namespace duration_compare_test

}	// namespace hamon_chrono_test
