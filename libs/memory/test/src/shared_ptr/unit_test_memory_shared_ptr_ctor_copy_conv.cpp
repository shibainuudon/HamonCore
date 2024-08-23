/**
 *	@file	unit_test_memory_shared_ptr_ctor_copy_conv.cpp
 *
 *	@brief	コピー変換コンストラクタのテスト
 *
 *	template<class Y>
 *	shared_ptr(const shared_ptr<Y>& r) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace ctor_copy_conv_test
{

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int      > const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1;
		hamon::shared_ptr<int const> sp2(sp1);
		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(sp2.get() == nullptr);
		VERIFY(sp2.use_count() == 0);
	}
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::shared_ptr<int const> sp2(sp1);
		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(*sp2.get() == 42);
		VERIFY(sp2.use_count() == 2);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int[]> sp2(sp1);
		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 2);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int const[]> sp2(sp1);
		VERIFY(sp1.get() == sp2.get());
		VERIFY(sp1.use_count() == sp2.use_count());
		VERIFY(sp2.get()[0] == 1);
		VERIFY(sp2.get()[1] == 2);
		VERIFY(sp2.get()[2] == 3);
		VERIFY(sp2.use_count() == 2);
	}
	{
		hamon::shared_ptr<int[3]> sp1(new int[3]{1,2,3});
		hamon::shared_ptr<int const[3]> sp2(sp1);
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

GTEST_TEST(SharedPtrTest, CtorCopyConvTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_copy_conv_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
