/**
 *	@file	unit_test_memory_unique_ptr_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	unique_ptr(const unique_ptr&) = delete;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_trivially_copy_constructible.hpp>
#include <hamon/type_traits/is_implicitly_copy_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ctor_copy_test
{

GTEST_TEST(UniquePtrTest, CtorCopyTest)
{
	{
		using UP = hamon::unique_ptr<int>;
		static_assert(!hamon::is_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_nothrow_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_trivially_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_implicitly_copy_constructible<UP>::value, "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert(!hamon::is_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_nothrow_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_trivially_copy_constructible<UP>::value, "");
		static_assert(!hamon::is_implicitly_copy_constructible<UP>::value, "");
	}
}

}	// namespace ctor_copy_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
