/**
 *	@file	unit_test_memory_shared_ptr_reset.cpp
 *
 *	@brief	reset() のテスト
 *
 *	void reset() noexcept;
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

namespace reset_test
{

template <typename SharedPtr, typename = void>
struct is_invocable_reset
	: public hamon::false_type {};

template <typename SharedPtr>
struct is_invocable_reset<SharedPtr,
	hamon::void_t<decltype(hamon::declval<SharedPtr>().reset())>>
	: public hamon::true_type {};

static_assert( is_invocable_reset<hamon::shared_ptr<int>>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[]>>::value, "");
static_assert( is_invocable_reset<hamon::shared_ptr<int[2]>>::value, "");

static_assert(!is_invocable_reset<hamon::shared_ptr<int> const>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[]> const>::value, "");
static_assert(!is_invocable_reset<hamon::shared_ptr<int[2]> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int{42});
		VERIFY(sp.get() != nullptr);
		VERIFY(sp.use_count() == 1);
		VERIFY(*sp == 42);
		static_assert(noexcept(sp.reset()), "");
		sp.reset();
		VERIFY(sp.get() == nullptr);
		VERIFY(sp.use_count() == 0);
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
		static_assert(noexcept(sp1.reset()), "");
		sp1.reset();
		VERIFY(sp1.get() == nullptr);
		VERIFY(sp1.use_count() == 0);
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

GTEST_TEST(SharedPtrTest, ResetTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace reset_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
