/**
 *	@file	unit_test_algorithm_equal.cpp
 *
 *	@brief	equal のテスト
 */

#include <hamon/algorithm/equal.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace equal_test
{

GTEST_TEST(AlgorithmTest, EqualTest)
{
	HAMON_CXX11_CONSTEXPR int a1[] {0,1,2};
	HAMON_CXX11_CONSTEXPR int a2[] {0,1,2};
	HAMON_CXX11_CONSTEXPR int a3[] {0,1,3};
	HAMON_CXX11_CONSTEXPR int a4[] {2,1,2};
	HAMON_CXX11_CONSTEXPR int a5[] {0,1};
	HAMON_CXX11_CONSTEXPR int a6[] {0,1,2,3};

	HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a7{{0, 1, 2}};
	HAMON_CXX11_CONSTEXPR hamon::array<int, 3> a8{{1, 1, 2}};
	HAMON_CXX11_CONSTEXPR hamon::array<int, 2> a9{{0, 1}};
	HAMON_CXX11_CONSTEXPR hamon::array<int, 4> a10{{0, 1, 2, 3}};

	const hamon::vector<int> v1 {0,1,2};
	const hamon::vector<int> v2 {0,1,2,3};
	const hamon::vector<int> v3 {0,1,2,3};

	const std::list<int> l1 {0,1,2};
	const std::list<int> l2 {0,1,2,3};
	const std::list<int> l3 {0,1,4,3};

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a1), hamon::end(a1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a2), hamon::end(a2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a3), hamon::end(a3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a4), hamon::end(a4)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a5), hamon::end(a5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a6), hamon::end(a6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a7), hamon::end(a7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a8), hamon::end(a8)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a9), hamon::end(a9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a10), hamon::end(a10)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a3)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a4)));
//	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a6)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a7)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a8)));
//	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a9)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(a10)));

	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(v1), hamon::end(v1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(v2), hamon::end(v2)));
	EXPECT_TRUE (hamon::equal(hamon::begin(v2), hamon::end(v2), hamon::begin(v3), hamon::end(v3)));
	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(l1), hamon::end(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(l2), hamon::end(l2)));
	EXPECT_TRUE (hamon::equal(hamon::begin(l1), hamon::end(l1), hamon::begin(l1), hamon::end(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(l1), hamon::end(l1), hamon::begin(l2), hamon::end(l2)));
	EXPECT_FALSE(hamon::equal(hamon::begin(l2), hamon::end(l2), hamon::begin(l1), hamon::end(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(l2), hamon::end(l2), hamon::begin(l3), hamon::end(l3)));
	EXPECT_TRUE (hamon::equal(hamon::begin(v1), hamon::end(v1), hamon::begin(l1), hamon::end(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(v1), hamon::end(v1), hamon::begin(l2), hamon::end(l2)));
	EXPECT_FALSE(hamon::equal(hamon::begin(v2), hamon::end(v2), hamon::begin(l1), hamon::end(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(v3), hamon::end(v3), hamon::begin(l3), hamon::end(l3)));

	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(v1)));
	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(v2)));
	EXPECT_TRUE (hamon::equal(hamon::begin(v2), hamon::end(v2), hamon::begin(v3)));
	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(l1)));
	EXPECT_TRUE (hamon::equal(hamon::begin(a1), hamon::end(a1), hamon::begin(l2)));
	EXPECT_TRUE (hamon::equal(hamon::begin(l1), hamon::end(l1), hamon::begin(l1)));
	EXPECT_TRUE (hamon::equal(hamon::begin(l1), hamon::end(l1), hamon::begin(l2)));
//	EXPECT_TRUE (hamon::equal(hamon::begin(l2), hamon::end(l2), hamon::begin(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(l2), hamon::end(l2), hamon::begin(l3)));
	EXPECT_TRUE (hamon::equal(hamon::begin(v1), hamon::end(v1), hamon::begin(l1)));
	EXPECT_TRUE (hamon::equal(hamon::begin(v1), hamon::end(v1), hamon::begin(l2)));
//	EXPECT_TRUE (hamon::equal(hamon::begin(v2), hamon::end(v2), hamon::begin(l1)));
	EXPECT_FALSE(hamon::equal(hamon::begin(v3), hamon::end(v3), hamon::begin(l3)));
}

}	// namespace equal_test

}	// namespace hamon_algorithm_test
