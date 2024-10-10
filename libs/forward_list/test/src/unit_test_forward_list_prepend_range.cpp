/**
 *	@file	unit_test_forward_list_prepend_range.cpp
 *
 *	@brief	prepend_range のテスト
 *
 *	template<container-compatible-range<T> R>
 *	void prepend_range(R&& rg);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace prepend_range_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) ||	\
	defined(__cpp_lib_containers_ranges) && (__cpp_lib_containers_ranges >= 202202L)

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, PrependRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#endif

}	// namespace prepend_range_test

}	// namespace hamon_forward_list_test
