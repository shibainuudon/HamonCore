/**
 *	@file	unit_test_memory_shared_ptr_get.cpp
 *
 *	@brief	get のテスト
 *
 *	element_type* get() const noexcept;
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

namespace get_test
{

template <typename SharedPtr, typename = void>
struct is_invocable_get
	: public hamon::false_type {};

template <typename SharedPtr>
struct is_invocable_get<SharedPtr,
	hamon::void_t<decltype(hamon::declval<SharedPtr>().get())>>
	: public hamon::true_type {};

static_assert( is_invocable_get<hamon::shared_ptr<int>>::value, "");
static_assert( is_invocable_get<hamon::shared_ptr<int[]>>::value, "");
static_assert( is_invocable_get<hamon::shared_ptr<int[2]>>::value, "");

static_assert( is_invocable_get<hamon::shared_ptr<int> const>::value, "");
static_assert( is_invocable_get<hamon::shared_ptr<int[]> const>::value, "");
static_assert( is_invocable_get<hamon::shared_ptr<int[2]> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int(42);
		hamon::shared_ptr<int> const sp(p);
		static_assert(noexcept(sp.get()), "");
		static_assert(hamon::is_same<decltype(sp.get()), int*>::value, "");
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::shared_ptr<int[]> sp(p);
		static_assert(noexcept(sp.get()), "");
		static_assert(hamon::is_same<decltype(sp.get()), int*>::value, "");
		VERIFY(sp.get() == p);
	}
	{
		auto p = new int[3]{1,2,3};
		hamon::shared_ptr<int[3]> sp(p);
		static_assert(noexcept(sp.get()), "");
		static_assert(hamon::is_same<decltype(sp.get()), int*>::value, "");
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

GTEST_TEST(SharedPtrTest, GetTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace get_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
