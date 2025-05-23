﻿/**
 *	@file	unit_test_memory_shared_ptr_reset_pointer_deleter.cpp
 *
 *	@brief	reset(Y* p, D d) のテスト
 *
 *	template<class Y, class D>
 *	void reset(Y* p, D d);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/memory/default_delete.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace reset_pointer_deleter_test
{

template <typename SharedPtr, typename Y, typename D, typename = void>
struct is_invocable_reset
	: public hamon::false_type {};

template <typename SharedPtr, typename Y, typename D>
struct is_invocable_reset<SharedPtr, Y, D,
	hamon::void_t<decltype(hamon::declval<SharedPtr>().reset(hamon::declval<Y>(), hamon::declval<D>()))>>
	: public hamon::true_type {};

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

static_assert( is_invocable_reset<hamon::shared_ptr<int>, int*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[]>, int*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[2]>, int*, D1>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int> const, int*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]> const, int*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]> const, int*, D1>::value, "");

#if !defined(HAMON_USE_STD_SHARED_PTR)
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, int*, D2>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, int const*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const>, int*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, int*, D3>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base>, Base*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived>, Base*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int>, void*, D1>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, int*, D2>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, int const*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[]>, int*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, int*, D3>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base[]>, Base*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Base[]>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived[]>, Base*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived[]>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]>, void*, D1>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, int*, D2>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, int const*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int const[2]>, int*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, int*, D3>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Base[2]>, Base*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Base[2]>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<Derived[2]>, Base*, D1>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<Derived[2]>, Derived*, D1>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]>, void*, D1>::value, "");
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
		hamon::default_delete<int> d{};
		static_assert(!noexcept(sp.reset(p, d)), "");
		sp.reset(p, d);
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
		hamon::default_delete<int> d{};
		static_assert(!noexcept(sp1.reset(p, d)), "");
		sp1.reset(p, d);
		VERIFY(sp1.get() != nullptr);
		VERIFY(sp1.use_count() == 1);
		VERIFY(*sp1 == 20);
		VERIFY(sp2.get() != nullptr);
		VERIFY(sp2.use_count() == 1);
		VERIFY(*sp2 == 42);
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

GTEST_TEST(SharedPtrTest, ResetPointerDeleterTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace reset_pointer_deleter_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
