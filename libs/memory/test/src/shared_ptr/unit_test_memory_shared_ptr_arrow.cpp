/**
 *	@file	unit_test_memory_shared_ptr_arrow.cpp
 *
 *	@brief	operator-> のテスト
 *
 *	T* operator->() const noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace arrow_test
{

struct X
{
	int i;
};

template <typename SharedPtr, typename = void>
struct is_invocable_arrow
	: public hamon::false_type {};

template <typename SharedPtr>
struct is_invocable_arrow<SharedPtr,
	hamon::void_t<decltype(hamon::declval<SharedPtr>().operator->())>>
	: public hamon::true_type {};

static_assert( is_invocable_arrow<hamon::shared_ptr<int>>::value, "");
static_assert(!is_invocable_arrow<hamon::shared_ptr<int[]>>::value, "");
static_assert(!is_invocable_arrow<hamon::shared_ptr<int[2]>>::value, "");
static_assert( is_invocable_arrow<hamon::shared_ptr<void>>::value, "");

static_assert( is_invocable_arrow<hamon::shared_ptr<int> const>::value, "");
static_assert(!is_invocable_arrow<hamon::shared_ptr<int[]> const>::value, "");
static_assert(!is_invocable_arrow<hamon::shared_ptr<int[2]> const>::value, "");
static_assert( is_invocable_arrow<hamon::shared_ptr<void> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int(10);
		hamon::shared_ptr<int> const sp(p);
		static_assert(noexcept(sp.operator->()), "");
		static_assert(hamon::is_same<decltype(sp.operator->()), int*>::value, "");
		VERIFY(sp.operator->() == p);
	}
	{
		auto p = new int(20);
		hamon::shared_ptr<int const> sp(p);
		static_assert(noexcept(sp.operator->()), "");
		static_assert(hamon::is_same<decltype(sp.operator->()), int const*>::value, "");
		VERIFY(sp.operator->() == p);
	}
	{
		hamon::shared_ptr<X> sp(new X{42});
		VERIFY(sp->i == 42);
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

GTEST_TEST(SharedPtrTest, ArrowTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace arrow_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
