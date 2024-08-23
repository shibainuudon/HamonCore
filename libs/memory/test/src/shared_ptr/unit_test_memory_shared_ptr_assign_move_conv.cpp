/**
 *	@file	unit_test_memory_shared_ptr_assign_move_conv.cpp
 *
 *	@brief	ムーブ変換代入演算子のテスト
 *
 *	template<class Y>
 *	shared_ptr& operator=(shared_ptr<Y>&& r) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace assign_move_conv_test
{

#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_DINKUMWARE))
static_assert( hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::shared_ptr<int const[3]> &&>::value, "");

static_assert( hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int      > &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      [3]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const[3]> &&>::value, "");
#endif

static_assert( hamon::is_nothrow_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int[3]> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int[]> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int[3]> &&>::value, "");

static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int const>, hamon::shared_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int[]>, hamon::shared_ptr<int[3]> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int[3]> &&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::shared_ptr<int const> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = hamon::move(sp1));
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(*sp2.get() == 42);
		VERIFY(sp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int[]> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = hamon::move(sp1));
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int const[]> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = hamon::move(sp1));
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int const[3]> sp2;

		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);

		auto& r = (sp2 = hamon::move(sp1));
		VERIFY(&r == &sp2);

		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 1);
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

GTEST_TEST(SharedPtrTest, AssignMoveConvTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace assign_move_conv_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
