/**
 *	@file	unit_test_memory_unique_ptr_assign_copy.cpp
 *
 *	@brief	コピー代入のテスト
 *
 *	unique_ptr& operator=(const unique_ptr&) = delete;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace assign_copy_test
{

GTEST_TEST(UniquePtrTest, AssignCopyTest)
{
	{
		using UP = hamon::unique_ptr<int>;
		static_assert(!hamon::is_copy_assignable<UP>::value, "");
		static_assert(!hamon::is_nothrow_copy_assignable<UP>::value, "");
		static_assert(!hamon::is_trivially_copy_assignable<UP>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert(!hamon::is_copy_assignable<UP>::value, "");
		static_assert(!hamon::is_nothrow_copy_assignable<UP>::value, "");
		static_assert(!hamon::is_trivially_copy_assignable<UP>::value, "");
	}
}

}	// namespace assign_copy_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
