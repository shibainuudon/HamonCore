/**
 *	@file	unit_test_new_bad_alloc.cpp
 *
 *	@brief	bad_alloc のテスト
 */

#include <hamon/new/bad_alloc.hpp>
#include <gtest/gtest.h>

namespace hamon_new_test
{

namespace bad_alloc_test
{

GTEST_TEST(NewTest, BadAllocTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_bad_alloc(), hamon::bad_alloc);
#endif
}

}	// namespace bad_alloc_test

}	// namespace hamon_new_test
