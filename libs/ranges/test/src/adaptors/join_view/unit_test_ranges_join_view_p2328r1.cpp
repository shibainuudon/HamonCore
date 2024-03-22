/**
 *	@file	unit_test_ranges_join_view_p2328r1.cpp
 *
 *	@brief	P2328R1 のテスト
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/ranges/adaptors/transform_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>

namespace hamon_ranges_test
{
namespace join_view_test
{
namespace p2328r1_test
{

struct Person
{
	int age;
	std::string name;
};

struct Fn
{
	std::string& operator()(Person& p) const
	{
		return p.name;
	}
};

GTEST_TEST(RangesTest, JoinViewP2328R1Test)
{
	// P2328R1
	std::vector<Person> v
	{
		{20, "Alice"},
		{30, "Bob"},
		{10, "Carol"},
	};

	auto r = v |
		hamon::views::transform(Fn{}) |
		hamon::views::join;
	std::string expected = "AliceBobCarol";
	EXPECT_TRUE(hamon::ranges::equal(expected, r));
}

}	// namespace p2328r1_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
