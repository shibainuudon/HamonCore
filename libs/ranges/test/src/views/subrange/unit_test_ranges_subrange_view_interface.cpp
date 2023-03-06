/**
 *	@file	unit_test_ranges_subrange_view_interface.cpp
 *
 *	@brief	view_interface<ranges::subrange> のテスト
 */

#include <hamon/ranges/views/subrange.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace subrange_test
{
namespace view_interface_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {1,2,3,4,5};
	{
		hamon::ranges::subrange<int*> sr(a);
		VERIFY(sr.front() == 1);
		VERIFY(sr.back()  == 5);
		VERIFY(sr[1]      == 2);
		VERIFY(sr[2]      == 3);
		VERIFY(sr.data()  == a);
		sr.front() = 11;
		sr.back()  = 12;
		sr[1]      = 13;
	}
	{
		hamon::ranges::subrange<int*> const sr(a);
		VERIFY(sr.front() == 11);
		VERIFY(sr.back()  == 12);
		VERIFY(sr[1]      == 13);
		VERIFY(sr[2]      == 3);
		VERIFY(sr.data()  == a);
	}
	return true;
}

GTEST_TEST(RangesTest, SubrangeViewInterfaceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

#undef VERIFY

}	// namespace view_interface_test
}	// namespace subrange_test
}	// namespace hamon_ranges_test
