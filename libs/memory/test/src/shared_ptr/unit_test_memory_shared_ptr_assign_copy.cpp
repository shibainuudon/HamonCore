﻿/**
 *	@file	unit_test_memory_shared_ptr_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	shared_ptr& operator=(const shared_ptr& r) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace assign_copy_test
{

static_assert( hamon::is_copy_assignable<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::shared_ptr<int[]>>::value, "");
static_assert( hamon::is_copy_assignable<hamon::shared_ptr<int[3]>>::value, "");

static_assert( hamon::is_nothrow_copy_assignable<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::shared_ptr<int[]>>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<hamon::shared_ptr<int[3]>>::value, "");

static_assert(!hamon::is_trivially_copy_assignable<hamon::shared_ptr<int>>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<hamon::shared_ptr<int[]>>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<hamon::shared_ptr<int[3]>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::shared_ptr<int> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = sp1);
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(*sp2.get() == 42);
		VERIFY(sp2.use_count() == 2);
	}
	{
		hamon::shared_ptr<int[]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int[]> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = sp1);
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 2);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int[3]> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = sp1);
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 2);
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(SharedPtrTest, AssignCopyTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace assign_copy_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
