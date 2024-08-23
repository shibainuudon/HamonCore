/**
 *	@file	unit_test_memory_shared_ptr_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~shared_ptr();
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace dtor_test
{

static_assert( hamon::is_destructible<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_nothrow_destructible<hamon::shared_ptr<int>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::shared_ptr<int>>::value, "");

struct X
{
	~X()
	{
		++dtor_count;
	}

	static int dtor_count;
};

int X::dtor_count = 0;

GTEST_TEST(SharedPtrTest, DtorTest)
{
	X::dtor_count = 0;
	{
		hamon::shared_ptr<X> sp1(new X);
	}
	EXPECT_EQ(1, X::dtor_count);

	X::dtor_count = 0;
	{
		hamon::shared_ptr<X> sp1(new X);
		hamon::shared_ptr<X> sp2(new X);
	}
	EXPECT_EQ(2, X::dtor_count);

	X::dtor_count = 0;
	{
		hamon::shared_ptr<X> sp1(new X);
		hamon::shared_ptr<X> sp2(sp1);
	}
	EXPECT_EQ(1, X::dtor_count);
}

}	// namespace dtor_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
