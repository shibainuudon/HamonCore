/**
 *	@file	unit_test_utility_as_const.cpp
 *
 *	@brief	as_const のテスト
 */

#include <hamon/utility/as_const.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(UtilityTest, AsConstTest)
{
	hamon::string mutable_string = "Hello World!";
	const hamon::string& const_view = hamon::as_const(mutable_string);

	EXPECT_TRUE(const_view == mutable_string);
	EXPECT_TRUE(hamon::as_const(mutable_string) == mutable_string);

	auto iter1 = mutable_string.begin();
	auto iter2 = hamon::as_const(mutable_string).begin();

	static_assert(hamon::is_same<decltype(iter1), hamon::string::iterator>::value, "");
	static_assert(hamon::is_same<decltype(iter2), hamon::string::const_iterator>::value, "");
}
