/**
 *	@file	unit_test_multiset_op_assign.cpp
 *
 *	@brief	operator= のテスト
 */

#include <hamon/set/multiset.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace op_assign_test
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

GTEST_TEST(MultisetTest, OpAssignTest)
{
	// https://en.cppreference.com/w/cpp/container/multiset/operator%3D

	hamon::multiset<int> x {1, 2, 3}, y, z;
	const auto w = {4, 5, 6, 7};

	EXPECT_EQ("{1, 2, 3}", ToString(x));
	EXPECT_EQ("{}", ToString(y));
	EXPECT_EQ("{}", ToString(z));

	y = x;
	EXPECT_EQ("{1, 2, 3}", ToString(x));
	EXPECT_EQ("{1, 2, 3}", ToString(y));

	z = hamon::move(x);
	EXPECT_EQ("{}", ToString(x));
	EXPECT_EQ("{1, 2, 3}", ToString(z));

	z = w;
	EXPECT_EQ("{4, 5, 6, 7}", ToString(z));
}

}	// namespace op_assign_test

}	// namespace hamon_multiset_test
