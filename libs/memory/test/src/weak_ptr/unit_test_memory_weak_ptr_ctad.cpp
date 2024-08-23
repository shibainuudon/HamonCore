﻿/**
 *	@file	unit_test_memory_weak_ptr_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class T>
 *	weak_ptr(shared_ptr<T>) -> weak_ptr<T>;
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

namespace ctad_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::shared_ptr<int> sp(new int{42});
		hamon::weak_ptr wp(sp);
		static_assert(hamon::is_same<decltype(wp), hamon::weak_ptr<int>>::value, "");
		VERIFY(*wp.lock() == 42);
	}
#endif
	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONSTEXPR_DYNAMIC_ALLOC) && \
	!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000))
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#else
#define MEMORY_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#endif

GTEST_TEST(WeakPtrTest, CtadTest)
{
	MEMORY_TEST_CONSTEXPR_EXPECT_TRUE(test());
}

#undef MEMORY_TEST_CONSTEXPR_EXPECT_TRUE

}	// namespace ctad_test

}	// namespace weak_ptr_test

}	// namespace hamon_memory_test