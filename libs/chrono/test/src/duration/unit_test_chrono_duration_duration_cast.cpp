/**
 *	@file	unit_test_chrono_duration_duration_cast.cpp
 *
 *	@brief	duration_cast() のテスト
 *
 *	template<class ToDuration, class Rep, class Period>
 *	constexpr ToDuration duration_cast(const duration<Rep, Period>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_duration_cast_test
{

template <typename ToDuration, typename Duration, typename = void>
struct is_invocable_duration_cast
	: public hamon::false_type {};

template <typename ToDuration, typename Duration>
struct is_invocable_duration_cast<ToDuration, Duration,
	hamon::void_t<decltype(hamon::chrono::duration_cast<ToDuration>(hamon::declval<Duration>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_duration_cast<hamon::chrono::duration<int>, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_duration_cast<hamon::chrono::duration<int>, hamon::chrono::duration<float>>::value, "");
static_assert( is_invocable_duration_cast<hamon::chrono::duration<float>, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_duration_cast<hamon::chrono::duration<float>, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_duration_cast<int, hamon::chrono::duration<int>>::value, "");
static_assert(!is_invocable_duration_cast<hamon::chrono::duration<int>, int>::value, "");

GTEST_TEST(DurationTest, DurationCastTest)
{
	using hamon::chrono::duration_cast;
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<int, hamon::ratio<1>>;
		static_assert(hamon::is_same<
			decltype(duration_cast<Duration2>(hamon::declval<Duration1>())),
			Duration2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(duration_cast<Duration2>(hamon::declval<Duration1>())), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-3900}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-3500}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-3100}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-3000}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-2900}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-2500}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-2100}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-2000}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-1900}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-1500}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-1100}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{-1000}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ -900}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ -500}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ -100}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{    0}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{  100}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{  500}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{  900}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 1000}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 1100}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 1500}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 1900}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 2000}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 2100}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 2500}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 2900}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 3000}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 3100}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 3500}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{ 3900}).count(),  3);
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<1, 1000>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<1>>;
		static_assert(hamon::is_same<
			decltype(duration_cast<Duration2>(hamon::declval<Duration1>())),
			Duration2
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(duration_cast<Duration2>(hamon::declval<Duration1>())), "");
#endif

		{
			HAMON_CXX11_CONSTEXPR Duration1 d1{1500};
			HAMON_CXX11_CONSTEXPR Duration2 d2 = duration_cast<Duration2>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.count(), 1.5f);
		}
		{
			HAMON_CXX11_CONSTEXPR Duration1 d1{-1500};
			HAMON_CXX11_CONSTEXPR Duration2 d2 = duration_cast<Duration2>(d1);
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(d2.count(), -1.5f);
		}
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<17>>;
		using Duration2 = hamon::chrono::duration<int, hamon::ratio<23>>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{100}).count(), 73);
	}
	{
		using Duration1 = hamon::chrono::duration<int, hamon::ratio<17>>;
		using Duration2 = hamon::chrono::duration<float, hamon::ratio<23>>;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(duration_cast<Duration2>(Duration1{100}).count(), 100.f / 23 * 17);	// ≒ 73.91304347826087
	}
}

}	// namespace duration_duration_cast_test

}	// namespace hamon_chrono_test
