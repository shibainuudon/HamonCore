/**
 *	@file	unit_test_memory_shared_ptr_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(shared_ptr& r) noexcept;
 *
 *	template<class T>
 *	void swap(shared_ptr<T>& a, shared_ptr<T>& b) noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		auto p1 = new int(1);
		auto p2 = new int(2);
		hamon::shared_ptr<int> sp1(p1);
		hamon::shared_ptr<int> sp2(p2);

		VERIFY(sp1.get() == p1);
		VERIFY(sp2.get() == p2);

		static_assert(noexcept(sp1.swap(sp2)), "");
		sp1.swap(sp2);

		VERIFY(sp1.get() == p2);
		VERIFY(sp2.get() == p1);

		static_assert(noexcept(swap(sp1, sp2)), "");
		swap(sp1, sp2);

		VERIFY(sp1.get() == p1);
		VERIFY(sp2.get() == p2);
	}
	{
		auto p1 = new int[2]{1,2};
		auto p2 = new int[3]{3,4,5};
		hamon::shared_ptr<int[]> sp1(p1);
		hamon::shared_ptr<int[]> sp2(p2);

		VERIFY(sp1.get() == p1);
		VERIFY(sp2.get() == p2);

		static_assert(noexcept(sp1.swap(sp2)), "");
		sp1.swap(sp2);

		VERIFY(sp1.get() == p2);
		VERIFY(sp2.get() == p1);

		static_assert(noexcept(swap(sp1, sp2)), "");
		swap(sp1, sp2);

		VERIFY(sp1.get() == p1);
		VERIFY(sp2.get() == p2);
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

GTEST_TEST(SharedPtrTest, SwapTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace swap_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
