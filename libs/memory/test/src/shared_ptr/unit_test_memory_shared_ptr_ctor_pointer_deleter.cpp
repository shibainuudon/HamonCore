/**
 *	@file	unit_test_memory_shared_ptr_ctor_pointer_deleter.cpp
 *
 *	@brief	ポインタとデリータを引数に取るコンストラクタのテスト
 *
 *	template<class Y, class D>
 *	shared_ptr(Y* p, D d);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/functional/ref.hpp>
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

namespace ctor_pointer_deleter_test
{

struct Base {};
struct Derived : Base {};

struct D1
{
	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	D2(D2&&) = delete;

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D3
{
	void operator()(char* p) const { delete p; }
};

static_assert( hamon::is_constructible<hamon::shared_ptr<int>, int*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, int*, D2>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, int const*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const>, int*, D1>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, int*, D3>::value, "");
#endif
static_assert( hamon::is_constructible<hamon::shared_ptr<Base>, Base*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Base>, Derived*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived>, Base*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived>, Derived*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int>, void*, D1>::value, "");

static_assert( hamon::is_constructible<hamon::shared_ptr<int[]>, int*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, int*, D2>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, int const*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[]>, int*, D1>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, int*, D3>::value, "");
#endif
static_assert( hamon::is_constructible<hamon::shared_ptr<Base[]>, Base*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Base[]>, Derived*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived[]>, Base*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived[]>, Derived*, D1>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_DINKUMWARE))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[]>, void*, D1>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<int[2]>, int*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, int*, D2>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, int const*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<int const[2]>, int*, D1>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_LIBSTDCPP3))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, int*, D3>::value, "");
#endif
static_assert( hamon::is_constructible<hamon::shared_ptr<Base[2]>, Base*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Base[2]>, Derived*, D1>::value, "");
static_assert(!hamon::is_constructible<hamon::shared_ptr<Derived[2]>, Base*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<Derived[2]>, Derived*, D1>::value, "");
#if !(defined(HAMON_USE_STD_SHARED_PTR) && defined(HAMON_STDLIB_DINKUMWARE))
static_assert(!hamon::is_constructible<hamon::shared_ptr<int[2]>, void*, D1>::value, "");
#endif

static_assert( hamon::is_constructible<hamon::shared_ptr<void>, void*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, int*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, Base*, D1>::value, "");
static_assert( hamon::is_constructible<hamon::shared_ptr<void>, Derived*, D1>::value, "");

static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int>, int*, D1>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[]>, int*, D1>::value, "");
static_assert(!hamon::is_nothrow_constructible<hamon::shared_ptr<int[2]>, int*, D1>::value, "");

static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int>, int*, D1>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[]>, int*, D1>::value, "");
static_assert(!hamon::is_trivially_constructible<hamon::shared_ptr<int[2]>, int*, D1>::value, "");

static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int>, int*, D1>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[]>, int*, D1>::value, "");
static_assert( hamon::is_implicitly_constructible<hamon::shared_ptr<int[2]>, int*, D1>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int(3);
		hamon::shared_ptr<int> sp{p, hamon::default_delete<int>{}};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::shared_ptr<int[]> sp{p, hamon::default_delete<int[]>{}};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::shared_ptr<int[3]> sp{p, hamon::default_delete<int[]>{}};
		VERIFY(sp.use_count() == 1);
		VERIFY(sp.get() == p);
	}
	{
		hamon::default_delete<int> d;
		auto p = new int(3);
		hamon::shared_ptr<int> sp{p, hamon::ref(d)};
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

GTEST_TEST(SharedPtrTest, CtorPointerDeleterTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctor_pointer_deleter_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
