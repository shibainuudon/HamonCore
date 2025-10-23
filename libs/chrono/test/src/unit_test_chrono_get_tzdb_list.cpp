/**
 *	@file	unit_test_chrono_get_tzdb_list.cpp
 *
 *	@brief	get_tzdb_list のテスト
 *
 *	tzdb_list& get_tzdb_list();
 */

#include <hamon/chrono/get_tzdb_list.hpp>
#include <hamon/chrono/tzdb_list.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, GetTzdbListTest)
{
	static_assert(hamon::is_same<decltype(hamon::chrono::get_tzdb_list()), hamon::chrono::tzdb_list&>::value, "");
	static_assert(!noexcept(hamon::chrono::get_tzdb_list()), "");

	{
		auto& r1 = hamon::chrono::get_tzdb_list();
		auto& r2 = hamon::chrono::get_tzdb_list();
		EXPECT_TRUE(&r1 == &r2);
	}

	const hamon::chrono::tzdb_list& list = hamon::chrono::get_tzdb_list();

	EXPECT_TRUE(!list.front().version.empty());
	EXPECT_TRUE(hamon::distance(list.begin(), list.end()) == 1);
	EXPECT_TRUE(hamon::distance(list.cbegin(), list.cend()) == 1);
}

}	// namespace hamon_chrono_test
