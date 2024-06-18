/**
 *	@file	unit_test_chrono_duration_count.cpp
 *
 *	@brief	count() のテスト
 *
 *	constexpr rep count() const;
 */

#include <hamon/chrono/duration.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <ratio>
#include "constexpr_test.hpp"

namespace hamon_chrono_test
{

namespace duration_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Rep, typename Period>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Duration = hamon::chrono::duration<Rep, Period>;

	Duration const d{10};
	static_assert(hamon::is_same<decltype(d.count()), Rep>::value, "");
#if !defined(HAMON_USE_STD_CHRONO)
	static_assert(noexcept(d.count()), "");
#endif

	VERIFY(d.count() == 10);

	return true;
}

#undef VERIFY

GTEST_TEST(DurationTest, CountTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int, std::ratio<60>>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long, std::milli>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double, std::ratio<1, 30>>()));
}

}	// namespace duration_count_test

}	// namespace hamon_chrono_test
