/**
 *	@file	unit_test_chrono_get_tzdb.cpp
 *
 *	@brief	get_tzdb のテスト
 *
 *	const tzdb& get_tzdb();
 */

#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/chrono/tzdb.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, GetTzdbTest)
{
	static_assert(hamon::is_same<decltype(hamon::chrono::get_tzdb()), hamon::chrono::tzdb const&>::value, "");
	static_assert(!noexcept(hamon::chrono::get_tzdb()), "");

	auto& r1 = hamon::chrono::get_tzdb();
	auto& r2 = hamon::chrono::get_tzdb();
	EXPECT_TRUE(&r1 == &r2);
}

}	// namespace hamon_chrono_test
