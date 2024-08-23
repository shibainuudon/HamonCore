/**
 *	@file	unit_test_memory_shared_ptr_ctor_pointer.cpp
 *
 *	@brief	ポインタを引数に取るコンストラクタのテスト
 *
 *	template<class Y>
 *	explicit shared_ptr(Y* p);
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

namespace ctor_pointer_test
{

struct Base {};
struct Derived : Base {};

struct S1
{
	void operator delete(void*) noexcept = delete;
};

struct S2
{
	void operator delete[](void*) noexcept = delete;
};

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Base>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Base>, Derived*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived>, Derived*>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!hamon::is_constructible<hamon::shared_ptr<S1>, S1*>::value, "");
#endif
#endif
static_assert( hamon::is_constructible<hamon::shared_ptr<S2>, S2*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, void*>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Base[]>, Base*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Base[]>, Derived*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived[]>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived[]>, Derived*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<S1[]>, S1*>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!hamon::is_constructible<hamon::shared_ptr<S2[]>, S2*>::value, "");
#endif
#endif
#if !defined(HAMON_USE_STD_SHARED_PTR)
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, void*>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<int[3]>, int*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[3]>, int const*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Base[3]>, Base*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Base[3]>, Derived*>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived[3]>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived[3]>, Derived*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<S1[3]>, S1*>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!hamon::is_constructible<hamon::shared_ptr<S2[3]>, S2*>::value, "");
#endif
#endif
#if !defined(HAMON_USE_STD_SHARED_PTR)
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[3]>, void*>::value, "");
#endif

#if !defined(HAMON_USE_STD_SHARED_PTR)
static_assert(!hamon::is_constructible<hamon::shared_ptr<void>, void*>::value, "");
#endif
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, int*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, Base*>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, Derived*>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<Base>, Derived*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int const[]>, int*>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<Base[]>, Base*>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const>, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<Base>, Derived*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int const[]>, int*>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<Base[]>, Base*>::value, "");

static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int const>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<Base>, Derived*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<int const[]>, int*>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::shared_ptr<Base[]>, Base*>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int(3);
		hamon::shared_ptr<int> sp{p};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[4]{1,2,3,4};
		hamon::shared_ptr<int[]> sp{p};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::shared_ptr<int[3]> sp{p};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
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

GTEST_TEST(SharedPtrTest, CtorPointerTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_pointer_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
