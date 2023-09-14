/**
 *	@file	unit_test_algorithm_is_permutation.cpp
 *
 *	@brief	is_permutation のテスト
 */

#include <hamon/algorithm/is_permutation.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace is_permutation_test
{

HAMON_CONSTEXPR bool pred1(int x, int y)
{
	return x == y;
}

GTEST_TEST(AlgorithmTest, IsPermutationTest)
{
	{
		HAMON_CONSTEXPR_OR_CONST int a[] { 1, 2, 3 };
		HAMON_CONSTEXPR_OR_CONST int b[] { 1, 2, 3 };
		HAMON_CONSTEXPR_OR_CONST int c[] { 2, 3, 1 };
		HAMON_CONSTEXPR_OR_CONST int d[] { 3, 1, 2 };
		HAMON_CONSTEXPR_OR_CONST int e[] { 1, 2, 4 };
		HAMON_CONSTEXPR_OR_CONST int f[] { 3, 2, 3 };

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(a)));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::equal_to<>()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(d)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(e)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(f), pred1));
	}
	{
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 4> a {{ 4, 5, 6, 7 }};
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 4> b {{ 6, 4, 5, 7 }};
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 4> c {{ 6, 4, 7, 5 }};
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 4> d {{ 6, 4, 5, 4 }};
		HAMON_CONSTEXPR_OR_CONST hamon::array<int, 4> e {{ 4, 5, 6, 8 }};

		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(a), hamon::end(a)));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::equal_to<>()));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c)));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(d), hamon::end(d), pred1));
		HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(e), hamon::end(e), hamon::equal_to<>()));
	}
	{
		const hamon::vector<int> a { 1, 2, 3 };
		const hamon::vector<int> b { 2, 3, 1 };
		const hamon::vector<int> c { 2, 3, 4 };

		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), pred1));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), pred1));
	}
	{
		const hamon::list<int> a { 3, 2, 1 };
		const hamon::list<int> b { 2, 3, 1 };
		const hamon::list<int> c { 2, 3, 4 };

		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b)));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c)));
		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::equal_to<>()));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::equal_to<>()));
		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b)));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c)));
		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::equal_to<>()));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), hamon::equal_to<>()));
	}
	{
		const std::string a = "abc";
		const std::string b = "cba";
		const std::string c = "aba";

		EXPECT_TRUE (hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b), hamon::equal_to<>()));
		EXPECT_FALSE(hamon::is_permutation(hamon::begin(a), hamon::end(a), hamon::begin(c), hamon::end(c), hamon::equal_to<>()));
	}
}

}	// namespace is_permutation_test

}	// namespace hamon_algorithm_test
