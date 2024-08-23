/**
 *	@file	unit_test_memory_shared_ptr_assign_unique_ptr.cpp
 *
 *	@brief	unique_ptrからの代入演算子のテスト
 *
 *	template<class Y, class D>
 *	shared_ptr& operator=(unique_ptr<Y, D>&& r);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/unique_ptr.hpp>
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

namespace assign_unique_ptr_test
{

#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_DINKUMWARE))
static_assert( hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert( hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int      > &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_assignable<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const[3]> &&>::value, "");
#endif

static_assert( hamon::is_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert( hamon::is_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

static_assert(!hamon::is_nothrow_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_nothrow_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_trivially_assignable<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up(new int{42});
		hamon::shared_ptr<int> sp;

		VERIFY(sp.get() == nullptr);
		VERIFY(sp.use_count() == 0);

		auto& r = (sp = hamon::move(up));
		VERIFY(&r == &sp);

		VERIFY(up.get() == nullptr);
		VERIFY(*sp.get() == 42);
		VERIFY(sp.use_count() == 1);
	}
	{
		hamon::default_delete<int> d;
		hamon::unique_ptr<int, hamon::default_delete<int>&> up(new int{42}, d);
		hamon::shared_ptr<int> sp;

		auto& r = (sp = hamon::move(up));
		VERIFY(&r == &sp);

		VERIFY(up.get() == nullptr);
		VERIFY(*sp.get() == 42);
		VERIFY(sp.use_count() == 1);
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

GTEST_TEST(SharedPtrTest, AssignUniquePtrTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace assign_unique_ptr_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
