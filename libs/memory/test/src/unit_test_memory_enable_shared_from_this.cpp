/**
 *	@file	unit_test_memory_enable_shared_from_this.cpp
 *
 *	@brief	enable_shared_from_this のテスト
 */

#include <hamon/memory/enable_shared_from_this.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace enable_shared_from_this_test
{

struct X : public hamon::enable_shared_from_this<X>
{
	HAMON_CXX20_CONSTEXPR hamon::shared_ptr<X> f1()
	{
		return shared_from_this();
	}

	HAMON_CXX20_CONSTEXPR hamon::shared_ptr<X const> f2() const
	{
		return shared_from_this();
	}

	HAMON_CXX20_CONSTEXPR hamon::weak_ptr<X> f3()
	{
		return weak_from_this();
	}

	HAMON_CXX20_CONSTEXPR hamon::weak_ptr<X const> f4() const
	{
		return weak_from_this();
	}
};

static_assert(!hamon::is_default_constructible<hamon::enable_shared_from_this<X>>::value, "");
static_assert(!hamon::is_copy_constructible<hamon::enable_shared_from_this<X>>::value, "");
static_assert(!hamon::is_move_constructible<hamon::enable_shared_from_this<X>>::value, "");
static_assert(!hamon::is_copy_assignable<hamon::enable_shared_from_this<X>>::value, "");
static_assert(!hamon::is_move_assignable<hamon::enable_shared_from_this<X>>::value, "");
static_assert(!hamon::is_destructible<hamon::enable_shared_from_this<X>>::value, "");

static_assert( hamon::is_default_constructible<X>::value, "");
static_assert( hamon::is_nothrow_default_constructible<X>::value, "");
static_assert(!hamon::is_trivially_default_constructible<X>::value, "");

static_assert( hamon::is_copy_constructible<X>::value, "");
static_assert( hamon::is_nothrow_copy_constructible<X>::value, "");
static_assert(!hamon::is_trivially_copy_constructible<X>::value, "");

static_assert( hamon::is_move_constructible<X>::value, "");
static_assert( hamon::is_nothrow_move_constructible<X>::value, "");
static_assert(!hamon::is_trivially_move_constructible<X>::value, "");

static_assert( hamon::is_copy_assignable<X>::value, "");
static_assert( hamon::is_nothrow_copy_assignable<X>::value, "");
static_assert(!hamon::is_trivially_copy_assignable<X>::value, "");

static_assert( hamon::is_move_assignable<X>::value, "");
static_assert( hamon::is_nothrow_move_assignable<X>::value, "");
static_assert(!hamon::is_trivially_move_assignable<X>::value, "");

static_assert( hamon::is_destructible<X>::value, "");
static_assert( hamon::is_nothrow_destructible<X>::value, "");
static_assert(!hamon::is_trivially_destructible<X>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<X> p(new X);
		hamon::shared_ptr<X> q = p->shared_from_this();
		VERIFY(p == q);
		VERIFY(p.owner_equal(q));
	}
	{
		hamon::shared_ptr<X> p(new X);
		hamon::shared_ptr<X> q = p->f1();
		VERIFY(p == q);
		VERIFY(p.owner_equal(q));
	}
	{
		hamon::shared_ptr<X> p(new X);
		hamon::shared_ptr<X const> q = p->f2();
		VERIFY(p == q);
		VERIFY(p.owner_equal(q));
	}
	{
		hamon::shared_ptr<X> p(new X);
		hamon::weak_ptr<X> q = p->f3();
		VERIFY(p == q.lock());
		VERIFY(p.owner_equal(q));
	}
	{
		hamon::shared_ptr<X> p(new X);
		hamon::weak_ptr<X const> q = p->f4();
		VERIFY(p == q.lock());
		VERIFY(p.owner_equal(q));
	}
	{
		X x1;
		X x2(x1);
		x1 = x2;
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

GTEST_TEST(MemoryTest, EnableSharedFromThisTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace enable_shared_from_this_test

}	// namespace hamon_memory_test
