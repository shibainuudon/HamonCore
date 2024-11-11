/**
 *	@file	unit_test_multiset_op_assign_copy.cpp
 *
 *	@brief	op_assign_copy のテスト
 *
 *	multiset& operator=(const multiset& x);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace op_assign_copy_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, OpAssignCopyTest)
{
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_copy_test

}	// namespace hamon_multiset_test
