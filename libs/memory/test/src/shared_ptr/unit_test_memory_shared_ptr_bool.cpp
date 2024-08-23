/**
 *	@file	unit_test_memory_shared_ptr_bool.cpp
 *
 *	@brief	operator bool のテスト
 *
 *	explicit operator bool() const noexcept;
 */

#include <hamon/memory/shared_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::shared_ptr<int> sp;
		static_assert(noexcept(static_cast<bool>(sp)), "");
		static_assert(hamon::is_same<decltype(static_cast<bool>(sp)), bool>::value, "");
		VERIFY(!sp);
		sp.reset(new int);
		VERIFY(sp);
	}
	{
		hamon::shared_ptr<int[]> sp(new int[3]{1,2,3});
		static_assert(noexcept(static_cast<bool>(sp)), "");
		static_assert(hamon::is_same<decltype(static_cast<bool>(sp)), bool>::value, "");
		VERIFY(sp);
		sp.reset();
		VERIFY(!sp);
	}
	{
		hamon::shared_ptr<int[3]> sp(new int[3]{1,2,3});
		static_assert(noexcept(static_cast<bool>(sp)), "");
		static_assert(hamon::is_same<decltype(static_cast<bool>(sp)), bool>::value, "");
		VERIFY(sp);
		sp.reset();
		VERIFY(!sp);
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

GTEST_TEST(SharedPtrTest, BoolTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace bool_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
