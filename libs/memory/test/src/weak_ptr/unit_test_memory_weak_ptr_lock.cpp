/**
 *	@file	unit_test_memory_weak_ptr_lock.cpp
 *
 *	@brief	lockのテスト
 *
 *	shared_ptr<T> lock() const noexcept;
 */

#include <hamon/memory/weak_ptr.hpp>
#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace weak_ptr_test
{

namespace lock_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::weak_ptr<int> wp;
		auto sp = wp.lock();
		static_assert(noexcept(wp.lock()), "");
		static_assert(hamon::is_same<decltype(sp), hamon::shared_ptr<int>>::value, "");
		VERIFY(sp.get() == nullptr);
	}
	{
		hamon::shared_ptr<int> sp1(new int(13));
		hamon::weak_ptr<int> wp(sp1);
		auto sp2 = wp.lock();
		VERIFY(sp1.get() == sp2.get());
		VERIFY(*sp2 == 13);
	}
	{
		hamon::shared_ptr<int> sp1(new int(13));
		hamon::weak_ptr<int> wp(sp1);
		sp1.reset();
		auto sp2 = wp.lock();
		VERIFY(sp2.get() == nullptr);
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

GTEST_TEST(WeakPtrTest, LockTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace lock_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
