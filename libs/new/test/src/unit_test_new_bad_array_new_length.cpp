/**
 *	@file	unit_test_new_bad_array_new_length.cpp
 *
 *	@brief	bad_array_new_length のテスト
 */

#include <hamon/new/bad_array_new_length.hpp>
#include <gtest/gtest.h>

namespace hamon_new_test
{

namespace bad_array_new_length_test
{

GTEST_TEST(NewTest, BadArrayNewLengthTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_bad_array_new_length(), hamon::bad_array_new_length);
#endif
}

}	// namespace bad_array_new_length_test

}	// namespace hamon_new_test
