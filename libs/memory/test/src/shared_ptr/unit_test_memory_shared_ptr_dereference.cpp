/**
 *	@file	unit_test_memory_shared_ptr_dereference.cpp
 *
 *	@brief	operator* のテスト
 *
 *	T& operator*() const noexcept;
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

namespace dereference_test
{

template <typename SharedPtr, typename = void>
struct is_invocable_deref
	: public hamon::false_type {};

template <typename SharedPtr>
struct is_invocable_deref<SharedPtr,
	hamon::void_t<decltype(*hamon::declval<SharedPtr>())>>
	: public hamon::true_type {};

static_assert( is_invocable_deref<hamon::shared_ptr<int>>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<int[]>>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<int[2]>>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<void>>::value, "");

static_assert( is_invocable_deref<hamon::shared_ptr<int> const>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<int[]> const>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<int[2]> const>::value, "");
static_assert(!is_invocable_deref<hamon::shared_ptr<void> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> const sp(new int(42));
		static_assert(noexcept(*sp), "");
		static_assert(hamon::is_same<decltype(*sp), int&>::value, "");
		VERIFY(*sp == 42);
	}
	{
		hamon::shared_ptr<int const> sp(new int(10));
		static_assert(noexcept(*sp), "");
		static_assert(hamon::is_same<decltype(*sp), int const&>::value, "");
		VERIFY(*sp == 10);
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

GTEST_TEST(SharedPtrTest, DereferenceTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace dereference_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
