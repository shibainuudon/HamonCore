/**
 *	@file	unit_test_chrono_duration_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr duration() = default;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_ctor_default_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	static_assert(hamon::is_default_constructible<Duration>::value, "");
	static_assert(hamon::is_nothrow_default_constructible<Duration>::value, "");
	static_assert(hamon::is_trivially_default_constructible<Duration>::value, "");
	static_assert(hamon::is_implicitly_default_constructible<Duration>::value, "");

	Duration d{};
	VERIFY(d.count() == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_ctor_default_test

}	// namespace hamon_chrono_test
