/**
 *	@file	unit_test_set_extract.cpp
 *
 *	@brief	extract のテスト
 *
 *	node_type extract(const_iterator position);
 *	node_type extract(const key_type& x);
 *	template<class K> node_type extract(K&& x);
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace extract_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, ExtractTest)
{
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace extract_test

}	// namespace hamon_set_test
