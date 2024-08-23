/**
 *	@file	unit_test_memory_shared_ptr_reset_pointer.cpp
 *
 *	@brief	reset(Y* p) のテスト
 *
 *	template<class Y>
 *	void reset(Y* p);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace reset_pointer_test
{

template <typename SharedPtr, typename Y, typename = void>
struct is_invocable_reset
	: public hamon::false_type {};

template <typename SharedPtr, typename Y>
struct is_invocable_reset<SharedPtr, Y,
	hamon::void_t<decltype(hamon::declval<SharedPtr>().reset(hamon::declval<Y>()))>>
	: public hamon::true_type {};


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

static_assert( is_invocable_reset<hamon::shared_ptr<int>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[]>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[2]>, int*>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int> const, int*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]> const, int*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]> const, int*>::value, "");

#if !defined(HAMON_USE_STD_SHARED_PTR)
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base>, Base*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base>, Derived*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived>, Base*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived>, Derived*>::value, "");
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!is_invocable_reset<hamon::shared_ptr<S1>, S1*>::value, "");
#endif
static_assert( is_invocable_reset<hamon::shared_ptr<S2>, S2*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, void*>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[]>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[]>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base[]>, Base*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Base[]>, Derived*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived[]>, Base*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived[]>, Derived*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<S1[]>, S1*>::value, "");
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!is_invocable_reset<hamon::shared_ptr<S2[]>, S2*>::value, "");
#endif
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, void*>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[2]>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[2]>, int const*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base[2]>, Base*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Base[2]>, Derived*>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived[2]>, Base*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived[2]>, Derived*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<S1[2]>, S1*>::value, "");
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1930)) && !defined(HAMON_GCC_VERSION)
static_assert(!is_invocable_reset<hamon::shared_ptr<S2[2]>, S2*>::value, "");
#endif
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, void*>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<void>, void*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<void>, int*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<void>, Base*>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<void>, Derived*>::value, "");
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int{42});
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(*sp == 42);
		auto p = new int{10};
		static_assert(!noexcept(sp.reset(p)), "");
		sp.reset(p);
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(*sp == 10);
	}
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::shared_ptr<int> sp2(sp1);
		VERIFY(sp1.get() != nullptr);
		VERIFY(sp1.use_count() == 2);
		VERIFY(*sp1 == 42);
		VERIFY(sp2.get() != nullptr);
		VERIFY(sp2.use_count() == 2);
		VERIFY(*sp2 == 42);
		auto p = new int{20};
		static_assert(!noexcept(sp2.reset(p)), "");
		sp2.reset(p);
		VERIFY(sp1.get() != nullptr);
		VERIFY(sp1.use_count() == 1);
		VERIFY(*sp1 == 42);
		VERIFY(sp2.get() != nullptr);
		VERIFY(sp2.use_count() == 1);
		VERIFY(*sp2 == 20);
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

GTEST_TEST(SharedPtrTest, ResetPointerTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace reset_pointer_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
