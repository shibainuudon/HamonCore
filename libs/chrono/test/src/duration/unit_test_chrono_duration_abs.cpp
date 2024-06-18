/**
 *	@file	unit_test_chrono_duration_abs.cpp
 *
 *	@brief	abs() のテスト
 *
 *	template<class Rep, class Period>
 *	constexpr duration<Rep, Period> abs(duration<Rep, Period> d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_abs_test
{

template <typename Duration, typename = void>
struct is_invocable_abs
	: public hamon::false_type {};

template <typename Duration>
struct is_invocable_abs<Duration, hamon::void_t<decltype(hamon::chrono::abs(hamon::declval<Duration>()))>>
	: public hamon::true_type {};

static_assert( is_invocable_abs<hamon::chrono::duration<int>>::value, "");
static_assert(!is_invocable_abs<hamon::chrono::duration<unsigned int>>::value, "");
static_assert( is_invocable_abs<hamon::chrono::duration<short, std::ratio<1, 1000>>>::value, "");
static_assert(!is_invocable_abs<hamon::chrono::duration<unsigned short, std::ratio<1, 1000>>>::value, "");
static_assert( is_invocable_abs<hamon::chrono::duration<long, std::ratio<60>>>::value, "");
static_assert(!is_invocable_abs<hamon::chrono::duration<unsigned long, std::ratio<60>>>::value, "");
static_assert( is_invocable_abs<hamon::chrono::duration<float>>::value, "");
static_assert( is_invocable_abs<hamon::chrono::duration<double, std::ratio<1, 10>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test1()
{
	using hamon::chrono::abs;
	{
		using Duration = hamon::chrono::duration<int, std::ratio<1, 1000>>;
		static_assert(hamon::is_same<
			decltype(abs(hamon::declval<Duration>())),
			Duration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(abs(hamon::declval<Duration>())), "");
#endif

		VERIFY(abs(Duration{-3}).count() == 3);
		VERIFY(abs(Duration{-2}).count() == 2);
		VERIFY(abs(Duration{-1}).count() == 1);
		VERIFY(abs(Duration{ 0}).count() == 0);
		VERIFY(abs(Duration{ 1}).count() == 1);
		VERIFY(abs(Duration{ 2}).count() == 2);
		VERIFY(abs(Duration{ 3}).count() == 3);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test2()
{
	using hamon::chrono::abs;
	{
		using Duration = hamon::chrono::duration<double, std::ratio<1, 1000>>;
		static_assert(hamon::is_same<
			decltype(abs(hamon::declval<Duration>())),
			Duration
		>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
		static_assert(noexcept(abs(hamon::declval<Duration>())), "");
#endif

		VERIFY(abs(Duration{-3.5}).count() == 3.5);
		VERIFY(abs(Duration{-2.5}).count() == 2.5);
		VERIFY(abs(Duration{-1.5}).count() == 1.5);
		VERIFY(abs(Duration{ 0.5}).count() == 0.5);
		VERIFY(abs(Duration{ 1.5}).count() == 1.5);
		VERIFY(abs(Duration{ 2.5}).count() == 2.5);
		VERIFY(abs(Duration{ 3.5}).count() == 3.5);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, AbsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace duration_abs_test

}	// namespace hamon_chrono_test
