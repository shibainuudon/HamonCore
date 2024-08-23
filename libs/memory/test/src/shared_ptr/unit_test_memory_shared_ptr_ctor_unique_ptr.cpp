/**
 *	@file	unit_test_memory_shared_ptr_ctor_unique_ptr.cpp
 *
 *	@brief	unique_ptrを引数に取るコンストラクタのテスト
 *
 *	template<class Y, class D>
 *	shared_ptr(unique_ptr<Y, D>&& r);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/unique_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace ctor_unique_ptr_test
{

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int      > &&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      > &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      []> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const[]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int      [3]> &&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::unique_ptr<int const[3]> &&>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::unique_ptr<int> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int const>, hamon::unique_ptr<int> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, hamon::unique_ptr<int[]> &&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int const[]>, hamon::unique_ptr<int[]> &&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int> up;
		hamon::shared_ptr<int> sp(hamon::move(up));
		VERIFY(up.get() == nullptr);
		VERIFY(sp.get() == nullptr);
		VERIFY(sp.use_count() == 0);
	}
	{
		hamon::unique_ptr<int[]> up;
		hamon::shared_ptr<int[]> sp(hamon::move(up));
		VERIFY(up.get() == nullptr);
		VERIFY(sp.get() == nullptr);
		VERIFY(sp.use_count() == 0);
	}
	{
		hamon::unique_ptr<int> up(new int{42});
		hamon::shared_ptr<int> sp(hamon::move(up));
		VERIFY(up.get() == nullptr);
		VERIFY(*sp.get() == 42);
		VERIFY(sp.use_count() == 1);
	}
	{
		hamon::unique_ptr<int[]> up(new int[3]{1,2,3});
		hamon::shared_ptr<int[]> sp(hamon::move(up));
		VERIFY(up.get() == nullptr);
		VERIFY(sp.get()[0] == 1);
		VERIFY(sp.get()[1] == 2);
		VERIFY(sp.get()[2] == 3);
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

GTEST_TEST(SharedPtrTest, CtorUniquePtrTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_unique_ptr_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
