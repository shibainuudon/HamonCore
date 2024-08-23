/**
 *	@file	unit_test_memory_shared_ptr_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr shared_ptr() noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace ctor_default_test
{

struct S
{
	S() = delete;
};

static_assert( hamon::is_default_constructible<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_default_constructible<hamon::shared_ptr<S>>::value, "");
static_assert( hamon::is_default_constructible<hamon::shared_ptr<int[]>>::value, "");
static_assert( hamon::is_default_constructible<hamon::shared_ptr<S[]>>::value, "");

static_assert( hamon::is_nothrow_default_constructible<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::shared_ptr<S>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::shared_ptr<int[]>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::shared_ptr<S[]>>::value, "");

static_assert(!hamon::is_trivially_default_constructible<hamon::shared_ptr<int>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::shared_ptr<S>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::shared_ptr<int[]>>::value, "");
static_assert(!hamon::is_trivially_default_constructible<hamon::shared_ptr<S[]>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::shared_ptr<int>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::shared_ptr<S>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::shared_ptr<int[]>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::shared_ptr<S[]>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<int[]> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<int[3]> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S[]> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S[4]> sp;
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
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

GTEST_TEST(SharedPtrTest, CtorDefaultTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_default_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
