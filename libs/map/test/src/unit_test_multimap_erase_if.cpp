/**
 *	@file	unit_test_multimap_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 */

#include <hamon/map/erase_if.hpp>
#include <hamon/map/multimap.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace erase_if_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct is_key_1
{
	template <typename T>
	bool operator()(T const& x) const
	{
		return x.first == 1;
	}
};

inline /*HAMON_CXX14_CONSTEXPR*/ bool
EraseIfTest()
{
	{
		hamon::multimap<int, char> m =
		{
			{3, 'a'},
			{1, 'b'},
			{4, 'c'},
		};
		auto r = hamon::erase_if(m, is_key_1{});
		VERIFY(r == 1);
		hamon::multimap<int, char> const m2 =
		{
			{3, 'a'},
			{4, 'c'},
		};
		VERIFY(hamon::ranges::equal(m, m2));
	}
	return true;
}

GTEST_TEST(MultiMapTest, EraseIfTest)
{
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(EraseIfTest());
}

#undef VERIFY

}	// namespace erase_if_test

}	// namespace hamon_multimap_test
