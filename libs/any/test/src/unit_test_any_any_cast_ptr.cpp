/**
 *	@file	unit_test_any_any_cast_ptr.cpp
 *
 *	@brief	any_cast関数のテスト
 *
 *	template<class T>
 *	const T* any_cast(const any* operand) noexcept;
 *
 *	template<class T>
 *	T* any_cast(any* operand) noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, AnyCastPtrTest)
{
	// (4)
	{
		hamon::any const a{3};
		auto p1 = hamon::any_cast<int>(&a);
		static_assert(hamon::is_same<decltype(p1), int const*>::value, "");
		EXPECT_EQ(3, *p1);

		auto p2 = hamon::any_cast<long>(&a);
		static_assert(hamon::is_same<decltype(p2), long const*>::value, "");
		EXPECT_TRUE(p2 == nullptr);
	}

	// (5)
	{
		hamon::any a{3};
		auto p1 = hamon::any_cast<int>(&a);
		static_assert(hamon::is_same<decltype(p1), int*>::value, "");
		EXPECT_EQ(3, *p1);

		auto p2 = hamon::any_cast<long>(&a);
		static_assert(hamon::is_same<decltype(p2), long*>::value, "");
		EXPECT_TRUE(p2 == nullptr);
	}
}
