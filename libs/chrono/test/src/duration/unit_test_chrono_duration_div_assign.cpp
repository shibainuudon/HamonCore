/**
 *	@file	unit_test_chrono_duration_div_assign.cpp
 *
 *	@brief	operator/=() のテスト
 *
 *	constexpr duration& operator/=(const duration& d);
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_div_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration d{10};
	static_assert(hamon::is_same<decltype(d /= 2), Duration&>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(d /= 2), "");
#endif

	auto& t = (d /= 2);
	VERIFY(&t == &d);
	VERIFY(d.count() == 5);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, DivAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_div_assign_test

}	// namespace hamon_chrono_test
