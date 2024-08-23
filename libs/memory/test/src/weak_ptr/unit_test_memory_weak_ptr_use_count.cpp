/**
 *	@file	unit_test_memory_weak_ptr_use_count.cpp
 *
 *	@brief	use_countのテスト
 *
 *	long use_count() const noexcept;
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

namespace use_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr<int> wp1(sp);
		static_assert(noexcept(wp1.use_count()), "");
		static_assert(hamon::is_same<decltype(wp1.use_count()), long>::value, "");
		VERIFY(wp1.use_count() == 1);

		hamon::weak_ptr<int> wp2(wp1);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 1);

		hamon::weak_ptr<int> wp3(wp2);
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 1);
		VERIFY(wp3.use_count() == 1);

		wp2.reset();
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);
		VERIFY(wp3.use_count() == 1);

		wp3.reset();
		VERIFY(wp1.use_count() == 1);
		VERIFY(wp2.use_count() == 0);
		VERIFY(wp3.use_count() == 0);

		wp1.reset();
		VERIFY(wp1.use_count() == 0);
		VERIFY(wp2.use_count() == 0);
		VERIFY(wp3.use_count() == 0);
	}
	{
		hamon::shared_ptr<int> sp1(new int{42});
		hamon::weak_ptr<int> wp(sp1);
		VERIFY(wp.use_count() == 1);

		hamon::shared_ptr<int> sp2(sp1);
		VERIFY(wp.use_count() == 2);

		hamon::shared_ptr<int> sp3(sp1);
		VERIFY(wp.use_count() == 3);

		sp3.reset();
		VERIFY(wp.use_count() == 2);

		sp1.reset();
		VERIFY(wp.use_count() == 1);

		sp2.reset();
		VERIFY(wp.use_count() == 0);
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

GTEST_TEST(WeakPtrTest, UseCountTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace use_count_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test
