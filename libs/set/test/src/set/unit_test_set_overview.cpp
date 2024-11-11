/**
 *	@file	unit_test_set_overview.cpp
 *
 *	@brief	set のテスト
 */

#include <hamon/set/set.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_set_test
{

namespace overview_test
{

template<typename T>
std::string ToString(const hamon::set<T>& set)
{
	std::stringstream out;
	auto n = set.size();
	out << "{";
	for (auto const& elm : set)
	{
		out << elm << (--n ? ", " : "");
	}
	out << "}";
	return out.str();
}

GTEST_TEST(SetTest, OverviewTest)
{
	// https://en.cppreference.com/w/cpp/container/set
	hamon::set<int> set{1, 5, 3};
	EXPECT_EQ("{1, 3, 5}", ToString(set));

	set.insert(2);
	EXPECT_EQ("{1, 2, 3, 5}", ToString(set));

	set.erase(1);
	EXPECT_EQ("{2, 3, 5}", ToString(set));

#if !defined(HAMON_USE_STD_SET) || (HAMON_CXX_STANDARD >= 20)
	EXPECT_TRUE(set.contains(3));
	EXPECT_FALSE(set.contains(4));
#endif

	hamon::string_view word = "element";
	hamon::set<char> characters(word.begin(), word.end());
	EXPECT_EQ("{e, l, m, n, t}", ToString(characters));
}

}	// namespace overview_test

}	// namespace hamon_set_test
