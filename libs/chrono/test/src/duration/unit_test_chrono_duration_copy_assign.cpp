/**
 *	@file	unit_test_chrono_duration_copy_assign.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	duration& operator=(const duration&) = default;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_copy_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_copy_assignable<Duration>::value, "");
	static_assert(hamon::is_nothrow_copy_assignable<Duration>::value, "");
	static_assert(hamon::is_trivially_copy_assignable<Duration>::value, "");

	Duration d1{1};
	Duration const d2{2};

	VERIFY(d1.count() == 1);
	VERIFY(d2.count() == 2);

	d1 = d2;

	VERIFY(d1.count() == 2);
	VERIFY(d2.count() == 2);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CopyAssignTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_copy_assign_test

}	// namespace hamon_chrono_test
