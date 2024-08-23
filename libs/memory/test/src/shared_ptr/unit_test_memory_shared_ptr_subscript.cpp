/**
 *	@file	unit_test_memory_shared_ptr_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	element_type& operator[](ptrdiff_t i) const;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
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

namespace subscript_test
{

template <typename SharedPtr, typename = void>
struct is_invocable_subscript
	: public hamon::false_type {};

template <typename SharedPtr>
struct is_invocable_subscript<SharedPtr,
	hamon::void_t<decltype(hamon::declval<SharedPtr>()[hamon::declval<hamon::ptrdiff_t>()])>>
	: public hamon::true_type {};

static_assert(!is_invocable_subscript<hamon::shared_ptr<int>>::value, "");
static_assert( is_invocable_subscript<hamon::shared_ptr<int[]>>::value, "");
static_assert( is_invocable_subscript<hamon::shared_ptr<int[2]>>::value, "");
static_assert(!is_invocable_subscript<hamon::shared_ptr<void>>::value, "");

static_assert(!is_invocable_subscript<hamon::shared_ptr<int> const>::value, "");
static_assert( is_invocable_subscript<hamon::shared_ptr<int[]> const>::value, "");
static_assert( is_invocable_subscript<hamon::shared_ptr<int[2]> const>::value, "");
static_assert(!is_invocable_subscript<hamon::shared_ptr<void> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p = new int[5]{1,2,3,4,5};
		hamon::shared_ptr<int[5]> const sp(p);
#if !defined(HAMON_USE_STD_SHARED_PTR)
		static_assert(noexcept(sp[0]), "");
#endif
		static_assert(hamon::is_same<decltype(sp[0]), int&>::value, "");
		VERIFY(sp[0] == 1);
		VERIFY(sp[1] == 2);
		VERIFY(sp[2] == 3);
		VERIFY(sp[3] == 4);
		VERIFY(sp[4] == 5);

		sp[1] = 42;
		sp[4] = 55;

		VERIFY(p[0] == 1);
		VERIFY(p[1] == 42);
		VERIFY(p[2] == 3);
		VERIFY(p[3] == 4);
		VERIFY(p[4] == 55);
	}
	{
		auto p = new int[3]{3,1,4};
		hamon::shared_ptr<int const[]> sp(p);
#if !defined(HAMON_USE_STD_SHARED_PTR)
		static_assert(noexcept(sp[0]), "");
#endif
		static_assert(hamon::is_same<decltype(sp[0]), int const&>::value, "");
		VERIFY(sp[0] == 3);
		VERIFY(sp[1] == 1);
		VERIFY(sp[2] == 4);
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

GTEST_TEST(SharedPtrTest, SubscriptTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace subscript_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
