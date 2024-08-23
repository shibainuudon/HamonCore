/**
 *	@file	unit_test_memory_shared_ptr_ctor_aliasing_move.cpp
 *
 *	@brief	エイリアシングコンストラクタのテスト
 *
 *	template<class Y>
 *	shared_ptr(shared_ptr<Y>&& r, element_type* p) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
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

namespace ctor_aliasing_move_test
{

struct X
{
	int i;
};

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int> &&, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X>   &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int> &&, int const*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X>   &&, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<char> &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<int> &&, char*>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int> &&, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<X>   &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int> &&, int const*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<X>   &&, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<char> &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::shared_ptr<int> &&, char*>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<int> &&, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<X>   &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<int> &&, int const*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<X>   &&, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<char> &&, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, hamon::shared_ptr<int> &&, char*>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X> &&, int*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[]> &&, int*>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[3]> &&, int*>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X> &&, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[]> &&, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[3]> &&, int*>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X> &&, int*>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[]> &&, int*>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::shared_ptr<X[3]> &&, int*>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<X> sp1(new X{3});
		hamon::shared_ptr<int> sp2(hamon::move(sp1), &(sp1->i));
		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(*sp2.get() == 3);
		VERIFY(sp2.use_count() == 1);
	}
	{
		hamon::shared_ptr<int> sp1(new int(3));
		hamon::shared_ptr<int> sp2(hamon::move(sp1), nullptr);
		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
		VERIFY(sp2.get() == nullptr);
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

GTEST_TEST(SharedPtrTest, CtorAliasingMoveTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_aliasing_move_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
