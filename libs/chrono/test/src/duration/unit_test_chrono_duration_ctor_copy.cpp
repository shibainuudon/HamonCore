/**
 *	@file	unit_test_chrono_duration_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	duration(const duration&) = default;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_ctor_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_copy_constructible<Duration>::value, "");
	static_assert(hamon::is_nothrow_copy_constructible<Duration>::value, "");
	static_assert(hamon::is_trivially_copy_constructible<Duration>::value, "");
	static_assert(hamon::is_implicitly_copy_constructible<Duration>::value, "");

	Duration const d1{42};
	Duration const d2{d1};
	VERIFY(d2.count() == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CtorCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, hamon::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, hamon::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, hamon::ratio<1, 30>>()));
}

}	// namespace duration_ctor_copy_test

}	// namespace hamon_chrono_test
