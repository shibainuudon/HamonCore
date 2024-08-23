/**
 *	@file	unit_test_memory_weak_ptr_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	~weak_ptr();
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_destructible.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace dtor_test
{

static_assert( hamon::is_destructible<hamon::weak_ptr<int>>::value, "");
static_assert( hamon::is_nothrow_destructible<hamon::weak_ptr<int>>::value, "");
static_assert(!hamon::is_trivially_destructible<hamon::weak_ptr<int>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int);
		VERIFY(1 == sp.use_count());
		{
			hamon::weak_ptr<int> wp(sp);
			VERIFY(1 == sp.use_count());
		}
		VERIFY(1 == sp.use_count());
	}
	{
		hamon::weak_ptr<int> wp;
		VERIFY(0 == wp.use_count());
		{
			hamon::shared_ptr<int> sp(new int);
			wp = sp;
			VERIFY(1 == wp.use_count());
		}
		VERIFY(0 == wp.use_count());
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

GTEST_TEST(WeakPtrTest, DtorTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace dtor_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
