/**
 *	@file	unit_test_set_pmr.cpp
 *
 *	@brief	pmr::set のテスト
 */

#include <hamon/set/set.hpp>
#include <hamon/string_view.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <string>
#include <sstream>

namespace hamon_set_test
{

namespace pmr_test
{

template<typename T>
std::string ToString(const hamon::pmr::set<T>& set)
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

GTEST_TEST(SetTest, PmrTest)
{
	// https://en.cppreference.com/w/cpp/container/set
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::set<int> set({1, 5, 3}, &mr);
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
	hamon::pmr::set<char> characters(word.begin(), word.end());
	EXPECT_EQ("{e, l, m, n, t}", ToString(characters));
}

}	// namespace pmr_test

}	// namespace hamon_set_test
