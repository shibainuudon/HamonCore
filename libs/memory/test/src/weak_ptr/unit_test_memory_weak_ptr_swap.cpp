/**
 *	@file	unit_test_memory_weak_ptr_swap.cpp
 *
 *	@brief	swapのテスト
 *
 *	void swap(weak_ptr& r) noexcept;
 *
 *	template<class T> void swap(weak_ptr<T>& a, weak_ptr<T>& b) noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1(new int(1));
		hamon::shared_ptr<int> sp2(new int(2));
		hamon::weak_ptr<int> wp1(sp1);
		hamon::weak_ptr<int> wp2(sp2);

		VERIFY(wp1.lock().get() == sp1.get());
		VERIFY(wp2.lock().get() == sp2.get());

		static_assert(noexcept(wp1.swap(wp2)), "");
		wp1.swap(wp2);

		VERIFY(wp1.lock().get() == sp2.get());
		VERIFY(wp2.lock().get() == sp1.get());

		static_assert(noexcept(swap(wp1, wp2)), "");
		swap(wp1, wp2);

		VERIFY(wp1.lock().get() == sp1.get());
		VERIFY(wp2.lock().get() == sp2.get());
	}
	{
		hamon::shared_ptr<int[]> sp1(new int[2]{1,2});
		hamon::shared_ptr<int[]> sp2(new int[3]{3,4,5});
		hamon::weak_ptr<int[]> wp1(sp1);
		hamon::weak_ptr<int[]> wp2(sp2);

		VERIFY(wp1.lock().get() == sp1.get());
		VERIFY(wp2.lock().get() == sp2.get());

		static_assert(noexcept(wp1.swap(wp2)), "");
		wp1.swap(wp2);

		VERIFY(wp1.lock().get() == sp2.get());
		VERIFY(wp2.lock().get() == sp1.get());

		static_assert(noexcept(swap(wp1, wp2)), "");
		swap(wp1, wp2);

		VERIFY(wp1.lock().get() == sp1.get());
		VERIFY(wp2.lock().get() == sp2.get());
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

GTEST_TEST(WeakPtrTest, SwapTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace swap_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
