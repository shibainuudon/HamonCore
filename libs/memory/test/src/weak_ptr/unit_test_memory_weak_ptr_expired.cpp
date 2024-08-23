/**
 *	@file	unit_test_memory_weak_ptr_expired.cpp
 *
 *	@brief	expiredのテスト
 *
 *	bool expired() const noexcept;
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

namespace expired_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::weak_ptr<int> wp;
		static_assert(noexcept(wp.expired()), "");
		static_assert(hamon::is_same<decltype(wp.expired()), bool>::value, "");

		VERIFY(wp.expired());

		hamon::shared_ptr<int> sp(new int{42});
		wp = sp;
		VERIFY(!wp.expired());

		wp.reset();
		VERIFY(wp.expired());
	}
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr<int> wp(sp);
		VERIFY(!wp.expired());

		sp.reset();
		VERIFY(wp.expired());
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

GTEST_TEST(WeakPtrTest, ExpiredTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace expired_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
