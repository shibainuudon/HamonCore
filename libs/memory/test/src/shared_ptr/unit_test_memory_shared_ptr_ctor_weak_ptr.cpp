/**
 *	@file	unit_test_memory_shared_ptr_ctor_weak_ptr.cpp
 *
 *	@brief	weak_ptrを引数に取るコンストラクタのテスト
 *
 *	template<class Y>
 *	explicit shared_ptr(const weak_ptr<Y>& r);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/bad_weak_ptr.hpp>
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

namespace ctor_weak_ptr_test
{

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int      > const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int[3]> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int[]> const&>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int[3]> const&>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int[3]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int[]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int[3]> const&>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int const>, hamon::weak_ptr<int> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, hamon::weak_ptr<int[3]> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int const[]>, hamon::weak_ptr<int[]> const&>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int const[3]>, hamon::weak_ptr<int[3]> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::weak_ptr<int> wp(sp1);
		hamon::shared_ptr<int> sp2(wp);
		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(*sp2.get() == 42);
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

GTEST_TEST(SharedPtrTest, CtorWeakPtrTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::weak_ptr<int> wp;
		EXPECT_THROW(hamon::shared_ptr<int> sp2(wp), hamon::bad_weak_ptr);
	}
#endif
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_weak_ptr_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
