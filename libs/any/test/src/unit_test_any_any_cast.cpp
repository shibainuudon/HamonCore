/**
 *	@file	unit_test_any_any_cast.cpp
 *
 *	@brief	any_cast関数のテスト
 *
 *	template<class T>
 *	T any_cast(const any& operand);
 * 
 *	template<class T>
 *	T any_cast(any& operand);
 * 
 *	template<class T>
 *	T any_cast(any&& operand);
 */

#include <hamon/any.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, AnyCastTest)
{
	// (1)
	{
		hamon::any const a{3};
		EXPECT_EQ(3, hamon::any_cast<int>(a));
		EXPECT_EQ(3, hamon::any_cast<int const&>(a));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)hamon::any_cast<long>(a), hamon::bad_any_cast);
#endif
	}

	// (2)
	{
		hamon::any a{3};
		EXPECT_EQ(3, hamon::any_cast<int>(a));
		EXPECT_EQ(3, hamon::any_cast<int&>(a));

#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)hamon::any_cast<long>(a), hamon::bad_any_cast);
#endif

		a = hamon::string("Meow");
		auto s = hamon::any_cast<hamon::string&>(a);
		EXPECT_EQ("Meow", s);
		hamon::any_cast<hamon::string&>(a) = hamon::string("Jane");
		EXPECT_EQ("Jane", hamon::any_cast<hamon::string>(a));
	}

	// (3)
	{
		hamon::any a{3};
		EXPECT_EQ(3, hamon::any_cast<int>(hamon::move(a)));
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::any a{3};
		EXPECT_THROW((void)hamon::any_cast<long>(hamon::move(a)), hamon::bad_any_cast);
	}
#endif
}
