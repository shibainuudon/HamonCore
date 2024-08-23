/**
 *	@file	unit_test_memory_weak_ptr_reset.cpp
 *
 *	@brief	resetのテスト
 *
 *	void reset() noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace reset_test
{

template <typename WeakPtr, typename = void>
struct is_invocable_reset
	: public hamon::false_type {};

template <typename WeakPtr>
struct is_invocable_reset<WeakPtr,
	hamon::void_t<decltype(hamon::declval<WeakPtr>().reset())>>
	: public hamon::true_type {};

static_assert( is_invocable_reset<hamon::weak_ptr<int>>::value, "");
static_assert( is_invocable_reset<hamon::weak_ptr<int[]>>::value, "");
static_assert( is_invocable_reset<hamon::weak_ptr<int[2]>>::value, "");

static_assert(!is_invocable_reset<hamon::weak_ptr<int> const>::value, "");
static_assert(!is_invocable_reset<hamon::weak_ptr<int[]> const>::value, "");
static_assert(!is_invocable_reset<hamon::weak_ptr<int[2]> const>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr<int> wp1(sp);
		hamon::weak_ptr<int> wp2(wp1);
		VERIFY(wp1.lock().get() == sp.get());
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 1);
		static_assert(noexcept(wp1.reset()), "");
		wp1.reset();
		VERIFY(wp1.lock().get() == nullptr);
		VERIFY(wp2.lock().get() == sp.get());
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 1);
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

GTEST_TEST(WeakPtrTest, ResetTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace reset_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
