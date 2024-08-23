/**
 *	@file	unit_test_memory_shared_ptr_ctor_nullptr.cpp
 *
 *	@brief	nullptrを引数に取るコンストラクタのテスト
 *
 *	constexpr shared_ptr(nullptr_t) noexcept : shared_ptr() { }
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
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

namespace ctor_nullptr_test
{

struct S
{
	S() = delete;
};

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<S>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<S[]>, hamon::nullptr_t>::value, "");

static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<S>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_nothrow_constructible<hamon::shared_ptr<S[]>, hamon::nullptr_t>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::nullptr_t>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<S>, hamon::nullptr_t>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<S[]>, hamon::nullptr_t>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<S>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<S[]>, hamon::nullptr_t>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp{nullptr};
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<int[]> sp{nullptr};
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<int[2]> sp{nullptr};
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S> sp(nullptr);
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S[]> sp(nullptr);
		VERIFY(sp.use_count() == 0);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<S[3]> sp(nullptr);
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

GTEST_TEST(SharedPtrTest, CtorNullptrTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_nullptr_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
