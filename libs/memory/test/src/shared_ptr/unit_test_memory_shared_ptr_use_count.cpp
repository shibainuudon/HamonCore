/**
 *	@file	unit_test_memory_shared_ptr_use_count.cpp
 *
 *	@brief	use_count のテスト
 *
 *	long use_count() const noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace use_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp1(new int{42});
		static_assert(noexcept(sp1.use_count()), "");
		static_assert(hamon::is_same<decltype(sp1.use_count()), long>::value, "");
		VERIFY(sp1.use_count() == 1);

		hamon::shared_ptr<int> sp2(sp1);
		VERIFY(sp1.use_count() == 2);
		VERIFY(sp2.use_count() == 2);

		hamon::shared_ptr<int> sp3(sp2);
		VERIFY(sp1.use_count() == 3);
		VERIFY(sp2.use_count() == 3);
		VERIFY(sp3.use_count() == 3);

		sp2.reset();
		VERIFY(sp1.use_count() == 2);
		VERIFY(sp2.use_count() == 0);
		VERIFY(sp3.use_count() == 2);

		sp3.reset();
		VERIFY(sp1.use_count() == 1);
		VERIFY(sp2.use_count() == 0);
		VERIFY(sp3.use_count() == 0);

		sp1.reset();
		VERIFY(sp1.use_count() == 0);
		VERIFY(sp2.use_count() == 0);
		VERIFY(sp3.use_count() == 0);
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

GTEST_TEST(SharedPtrTest, UseCountTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace use_count_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
