/**
 *	@file	unit_test_multiset_erase.cpp
 *
 *	@brief	erase のテスト
 */

#include <hamon/set/multiset.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace erase_test
{

template <typename T, typename C>
std::string ToString(const hamon::multiset<T, C>& set)
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

GTEST_TEST(MultisetTest, EraseTest)
{
	// https://en.cppreference.com/w/cpp/container/multiset/erase

	hamon::multiset<int> c = {1, 2, 3, 4, 1, 2, 3, 4};

	EXPECT_EQ("{1, 1, 2, 2, 3, 3, 4, 4}", ToString(c));

	// Erase all odd numbers
	for (auto it = c.begin(); it != c.end();)
	{
		if (*it % 2 != 0)
		{
			it = c.erase(it);
		}
		else
		{
			++it;
		}
	}
	EXPECT_EQ("{2, 2, 4, 4}", ToString(c));

	EXPECT_EQ(0u, c.erase(1));
	EXPECT_EQ(2u, c.erase(2));
	EXPECT_EQ(0u, c.erase(2));
	EXPECT_EQ("{4, 4}", ToString(c));
}

}	// namespace erase_test

}	// namespace hamon_multiset_test
