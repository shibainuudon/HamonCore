/**
 *	@file	unit_test_memory_weak_ptr_ctor_shared_ptr.cpp
 *
 *	@brief	shared_ptrからのコンストラクタのテスト
 *
 *	template<class Y>
 *	weak_ptr(const shared_ptr<Y>& r) noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace ctor_shared_ptr_test
{

static_assert( hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert( hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int      > const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int[3]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int      > const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int const> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int      []> const&>::value, "");
static_assert(!hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int const[]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int      [3]> const&>::value, "");
static_assert( hamon::is_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int const[3]> const&>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::weak_ptr<int const>, hamon::shared_ptr<int> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::weak_ptr<int[]>, hamon::shared_ptr<int[3]> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::weak_ptr<int const[]>, hamon::shared_ptr<int[]> const&>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::weak_ptr<int const[3]>, hamon::shared_ptr<int[3]> const&>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp;
		hamon::weak_ptr<int const> wp(sp);
		VERIFY(sp.get() == nullptr);
		VERIFY(wp.lock().get() == nullptr);
		VERIFY(sp.use_count() == 0);
		VERIFY(wp.use_count() == 0);
	}
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr<int const> wp(sp);
		VERIFY(wp.lock().get() == sp.get());
		VERIFY(sp.use_count() == 1);
		VERIFY(wp.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int[]> wp(sp);
		VERIFY(wp.lock().get() == sp.get());
		VERIFY(sp.use_count() == 1);
		VERIFY(wp.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int const[]> wp(sp);
		VERIFY(wp.lock().get() == sp.get());
		VERIFY(sp.use_count() == 1);
		VERIFY(wp.use_count() == 1);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		hamon::weak_ptr<int const[3]> wp(sp);
		VERIFY(wp.lock().get() == sp.get());
		VERIFY(sp.use_count() == 1);
		VERIFY(wp.use_count() == 1);
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

GTEST_TEST(WeakPtrTest, CtorSharedPtrTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_shared_ptr_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
