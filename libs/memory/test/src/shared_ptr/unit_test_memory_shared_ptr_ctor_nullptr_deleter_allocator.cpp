﻿/**
 *	@file	unit_test_memory_shared_ptr_ctor_nullptr_deleter_allocator.cpp
 *
 *	@brief	nullptrとデリータとアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class D, class A>
 *	shared_ptr(nullptr_t p, D d, A a);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/allocator.hpp>
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

namespace ctor_nullptr_deleter_allocator_test
{

struct D1
{
	HAMON_CXX14_CONSTEXPR void operator()(hamon::nullptr_t) const {}
};

struct D2
{
	D2(D2&&) = delete;

	HAMON_CXX14_CONSTEXPR void operator()(hamon::nullptr_t) const {}
};

struct D3
{
	HAMON_CXX14_CONSTEXPR void operator()(hamon::nullptr_t) const = delete;
};

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D2, hamon::allocator<char>>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D3, hamon::allocator<char>>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D2, hamon::allocator<char>>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D3, hamon::allocator<char>>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D2, hamon::allocator<char>>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D3, hamon::allocator<char>>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<void>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<void>, hamon::nullptr_t, D2, hamon::allocator<char>>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<void>, hamon::nullptr_t, D3, hamon::allocator<char>>::value, "");
#endif

static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[3]>, hamon::nullptr_t, D1, hamon::allocator<char>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::allocator<char> a;	// アロケータの要素型は何でも良い
		hamon::shared_ptr<int> sp{nullptr, D1{}, a};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::allocator<char> a;	// アロケータの要素型は何でも良い
		hamon::shared_ptr<int[]> sp{nullptr, D1{}, a};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::allocator<char> a;	// アロケータの要素型は何でも良い
		hamon::shared_ptr<int[3]> sp{nullptr, D1{}, a};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == nullptr);
	}
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000)) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(SharedPtrTest, CtorNullptrDeleterAllocatorTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_nullptr_deleter_allocator_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
