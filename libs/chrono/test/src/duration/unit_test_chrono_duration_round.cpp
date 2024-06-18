/**
 *	@file	unit_test_chrono_duration_round.cpp
 *
 *	@brief	round() のテスト
 *
 *	template<class ToDuration, class Rep, class Period>
 *	constexpr ToDuration round(const duration<Rep, Period>& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_round_test
{

template <typename ToDuration, typename Duration, typename = void>
struct is_invocable_round
	: public hamon::false_type {};

template <typename ToDuration, typename Duration>
struct is_invocable_round<ToDuration, Duration,
	hamon::void_t<decltype(hamon::chrono::round<ToDuration>(hamon::declval<Duration>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_round<hamon::chrono::duration<int>, hamon::chrono::duration<int>>::value, "");
static_assert( is_invocable_round<hamon::chrono::duration<int>, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_round<hamon::chrono::duration<float>, hamon::chrono::duration<int>>::value, "");
static_assert(!is_invocable_round<hamon::chrono::duration<float>, hamon::chrono::duration<float>>::value, "");
static_assert(!is_invocable_round<int, hamon::chrono::duration<int>>::value, "");
static_assert(!is_invocable_round<hamon::chrono::duration<int>, int>::value, "");

GTEST_TEST(DurationTest, RoundTest)
{
	using hamon::chrono::round;
	{
		using Duration = hamon::chrono::duration<int, std::ratio<1, 1000>>;
		using ToDuration = hamon::chrono::duration<int, std::ratio<1>>;
		static_assert(hamon::is_same<
			decltype(round<ToDuration>(hamon::declval<Duration>())),
			ToDuration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(round<ToDuration>(hamon::declval<Duration>())), "");
#endif

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-3900}).count(), -4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-3500}).count(), -4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-3100}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-3000}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-2900}).count(), -3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-2500}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-2100}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-2000}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-1900}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-1500}).count(), -2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-1100}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{-1000}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ -900}).count(), -1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ -500}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ -100}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{    0}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{  100}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{  500}).count(),  0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{  900}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 1000}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 1100}).count(),  1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 1500}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 1900}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 2000}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 2100}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 2500}).count(),  2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 2900}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 3000}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 3100}).count(),  3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 3500}).count(),  4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(round<ToDuration>(Duration{ 3900}).count(),  4);
	}
}

}	// namespace duration_round_test

}	// namespace hamon_chrono_test
