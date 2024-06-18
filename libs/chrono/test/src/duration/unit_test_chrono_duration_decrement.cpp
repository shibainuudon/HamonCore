/**
 *	@file	unit_test_chrono_duration_decrement.cpp
 *
 *	@brief	operator--() のテスト
 *
 *	constexpr duration& operator--();
 *	constexpr duration  operator--(int);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_decrement_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration d{10};
	static_assert(hamon::is_same<decltype(--d), Duration&>::value, "");
	static_assert(hamon::is_same<decltype(d--), Duration>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(--d), "");
	static_assert(noexcept(d--), "");
#endif

	{
		auto d2 = --d;
		VERIFY(d.count() == 9);
		VERIFY(d2.count() == 9);
	}
	{
		auto d2 = d--;
		VERIFY(d.count() == 8);
		VERIFY(d2.count() == 9);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, DecrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_decrement_test

}	// namespace hamon_chrono_test
