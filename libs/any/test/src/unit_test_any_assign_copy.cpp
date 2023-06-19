/**
 *	@file	unit_test_any_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	any& operator=(const any& rhs);
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <gtest/gtest.h>
#include <string>

namespace hamon_any_test
{

namespace assign_copy_test
{

static_assert(hamon::is_copy_assignable<hamon::any>::value, "");

#if !defined(HAMON_NO_EXCEPTIONS)
struct ThrowOnCopy
{
	ThrowOnCopy()
	{
	}

	ThrowOnCopy(ThrowOnCopy const&)
	{
		throw 42;
	}

	ThrowOnCopy(ThrowOnCopy&&)
	{
	}
};
#endif

GTEST_TEST(AnyTest, AssignCopyTest)
{
	{
		hamon::any const a{3};
		hamon::any b{};
		EXPECT_FALSE(b.has_value());
		b = a;
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(b));
	}
	{
		hamon::any const a{};
		hamon::any b{3};
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(b));
		b = a;
		EXPECT_FALSE(b.has_value());
	}
	{
		hamon::any const a{std::string("Hello")};
		hamon::any b{};
		EXPECT_FALSE(b.has_value());
		b = a;
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(b));
	}
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::any const a{ThrowOnCopy()};
		hamon::any b{};
		EXPECT_FALSE(b.has_value());

		// [any.assign]/1
		// No effects if an exception is thrown.
		EXPECT_THROW(b = a, int);
		EXPECT_FALSE(b.has_value());
	}
	{
		hamon::any const a{ThrowOnCopy()};
		hamon::any b{42};
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(42, hamon::any_cast<int>(b));

		// [any.assign]/1
		// No effects if an exception is thrown.
		EXPECT_THROW(b = a, int);
		EXPECT_EQ(42, hamon::any_cast<int>(b));
	}
#endif
}

}	// namespace assign_copy_test

}	// namespace hamon_any_test
