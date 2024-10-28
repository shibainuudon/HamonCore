/**
 *	@file	unit_test_inplace_vector_overview.cpp
 *
 *	@brief	inplace_vector のテスト
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/algorithm.hpp>
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_inplace_vector_test
{

namespace overview_test
{

struct Empty
{
};

struct Large
{
	int a[100];
};

static_assert( hamon::is_empty<hamon::inplace_vector<int, 0>>::value, "");
static_assert( hamon::is_empty<hamon::inplace_vector<float, 0>>::value, "");
static_assert( hamon::is_empty<hamon::inplace_vector<Empty, 0>>::value, "");
static_assert( hamon::is_empty<hamon::inplace_vector<Large, 0>>::value, "");
static_assert( hamon::is_empty<hamon::inplace_vector<hamon::string, 0>>::value, "");

static_assert(!hamon::is_empty<hamon::inplace_vector<int, 1>>::value, "");
static_assert(!hamon::is_empty<hamon::inplace_vector<float, 1>>::value, "");
static_assert(!hamon::is_empty<hamon::inplace_vector<Empty, 1>>::value, "");
static_assert(!hamon::is_empty<hamon::inplace_vector<Large, 1>>::value, "");
static_assert(!hamon::is_empty<hamon::inplace_vector<hamon::string, 1>>::value, "");

GTEST_TEST(InplaceVectorTest, OverviewTest)
{
	// https://en.cppreference.com/w/cpp/container/inplace_vector
	hamon::inplace_vector<int, 4> v1 {0, 1, 2};
	EXPECT_TRUE(v1.max_size() == 4);
	EXPECT_TRUE(v1.capacity() == 4);
	EXPECT_TRUE(v1.size() == 3);
	EXPECT_TRUE(hamon::ranges::equal(v1, hamon::array<int, 3>{0, 1, 2}));
	EXPECT_TRUE(v1[0] == 0);
	EXPECT_TRUE(v1.at(0) == 0);
	EXPECT_TRUE(v1.front() == 0);
	EXPECT_TRUE(*v1.begin() == 0);
	EXPECT_TRUE(v1.back() == 2);
	v1.push_back(3);
	EXPECT_TRUE(v1.back() == 3);
	EXPECT_TRUE(hamon::ranges::equal(v1, hamon::array<int, 4>{0, 1, 2, 3}));
	v1.resize(3);
	EXPECT_TRUE(hamon::ranges::equal(v1, hamon::array<int, 3>{0, 1, 2}));
	EXPECT_TRUE(v1.try_push_back(3) != nullptr);
	EXPECT_TRUE(v1.back() == 3);
	EXPECT_TRUE(v1.size() == 4);
	EXPECT_TRUE(v1.try_push_back(13) == nullptr); // no place
	EXPECT_TRUE(v1.back() == 3);
	EXPECT_TRUE(v1.size() == 4);
	v1.clear();
	EXPECT_TRUE(v1.size() == 0);
	EXPECT_TRUE(v1.empty());
}

}	// namespace overview_test

}	// namespace hamon_inplace_vector_test
