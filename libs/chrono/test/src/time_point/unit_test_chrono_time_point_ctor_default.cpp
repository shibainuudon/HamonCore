/**
 *	@file	unit_test_chrono_time_point_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr time_point();
 */

#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/ratio.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace time_point_ctor_default_test
{

struct MyClock
{};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Clock, typename Duration>
HAMON_CXX14_CONSTEXPR bool test()
{
	using TimePoint = hamon::chrono::time_point<Clock, Duration>;

	static_assert( hamon::is_default_constructible<TimePoint>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(!hamon::is_nothrow_default_constructible<TimePoint>::value, "");
#endif
	static_assert(!hamon::is_trivially_default_constructible<TimePoint>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<TimePoint>::value, "");

	TimePoint tp{};
	VERIFY(tp.time_since_epoch() == Duration::zero());

	return true;
}

#undef VERIFY

GTEST_TEST(TimePointTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<int, hamon::ratio<1, 1000>>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<MyClock, hamon::chrono::duration<float>>()));
}

}	// namespace time_point_ctor_default_test

}	// namespace hamon_chrono_test
