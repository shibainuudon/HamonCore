/**
 *	@file	unit_test_chrono_duration_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~duration() = default;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_dtor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_destructible<Duration>::value, "");
	static_assert(hamon::is_nothrow_destructible<Duration>::value, "");
	static_assert(hamon::is_trivially_destructible<Duration>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, DtorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_dtor_test

}	// namespace hamon_chrono_test
