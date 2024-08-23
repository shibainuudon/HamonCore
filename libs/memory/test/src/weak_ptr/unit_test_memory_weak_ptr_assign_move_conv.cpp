/**
 *	@file	unit_test_memory_weak_ptr_assign_move_conv.cpp
 *
 *	@brief	ムーブ変換代入演算子のテスト
 *
 *	template<class Y>
 *	weak_ptr& operator=(weak_ptr<Y>&& r) noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace assign_move_conv_test
{

#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_DINKUMWARE))
static_assert( hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int>, hamon::weak_ptr<int const[3]> &&>::value, "");

static_assert( hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int      > &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int[3]>, hamon::weak_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int const[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int      [3]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int const[3]> &&>::value, "");
#endif

static_assert( hamon::is_nothrow_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int[3]> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int[]> &&>::value, "");
static_assert( hamon::is_nothrow_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int[3]> &&>::value, "");

static_assert(!hamon::is_trivially_assignable<hamon::weak_ptr<int const>, hamon::weak_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::weak_ptr<int[]>, hamon::weak_ptr<int[3]> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::weak_ptr<int const[]>, hamon::weak_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::weak_ptr<int const[3]>, hamon::weak_ptr<int[3]> &&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr<int> wp1(sp);
		hamon::weak_ptr<int const> wp2;

		VERIFY(wp1.lock().get() == sp.get());
		VERIFY(wp2.lock().get() == nullptr);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);

		auto& r = (wp2 = hamon::move(wp1));
		VERIFY(&r == &wp2);

		VERIFY(wp1.lock().get() == nullptr);
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int[3]> wp1(sp);
		hamon::weak_ptr<int[]> wp2;

		VERIFY(wp1.lock().get() == sp.get());
		VERIFY(wp2.lock().get() == nullptr);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);

		auto& r = (wp2 = hamon::move(wp1));
		VERIFY(&r == &wp2);

		VERIFY(wp1.lock().get() == nullptr);
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int[3]> wp1(sp);
		hamon::weak_ptr<int const[]> wp2;

		VERIFY(wp1.lock().get() == sp.get());
		VERIFY(wp2.lock().get() == nullptr);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);

		auto& r = (wp2 = hamon::move(wp1));
		VERIFY(&r == &wp2);

		VERIFY(wp1.lock().get() == nullptr);
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int[3]> wp1(sp);
		hamon::weak_ptr<int const[3]> wp2;

		VERIFY(wp1.lock().get() == sp.get());
		VERIFY(wp2.lock().get() == nullptr);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);

		auto& r = (wp2 = hamon::move(wp1));
		VERIFY(&r == &wp2);

		VERIFY(wp1.lock().get() == nullptr);
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 1);
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

GTEST_TEST(WeakPtrTest, AssignMoveConvTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace assign_move_conv_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
