/**
 *	@file	unit_test_any_type.cpp
 *
 *	@brief	type関数のテスト
 *
 *	const type_info& type() const noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, TypeTest)
{
#if !defined(HAMON_NO_RTTI)
	{
		hamon::any a;
		EXPECT_TRUE(a.type() == typeid(void));
	}
	{
		hamon::any a{3};
		EXPECT_TRUE(a.type() == typeid(int));
	}
	{
		hamon::any a{hamon::string("hello")};
		EXPECT_TRUE(a.type() == typeid(hamon::string));
	}
#endif
}
