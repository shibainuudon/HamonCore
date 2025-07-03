/**
 *	@file	unit_test_chrono_duration_sub_assign.cpp
 *
 *	@brief	operator-=() のテスト
 *
 *	constexpr duration& operator-=(const duration& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_sub_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration d{10};
	static_assert(hamon::is_same<decltype(d -= d), Duration&>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(d -= d), "");
#endif

	auto& t = (d -= Duration{1});
	VERIFY(&t == &d);
	VERIFY(d.count() == 9);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, SubAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, hamon::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, hamon::ratio<1, 30>>()));
}

}	// namespace duration_sub_assign_test

}	// namespace hamon_chrono_test
