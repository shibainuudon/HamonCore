/**
 *	@file	unit_test_algorithm_lexicographical_compare_three_way.cpp
 *
 *	@brief	lexicographical_compare_three_way のテスト
 */

#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_algorithm_test
{

namespace lexicographical_compare_three_way_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool
test01(int i)
{
	int  a1[] = { 0, 1, 2, 3, 4, 5, 6, i, 8 };
	long a2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 0, a2, a2 + 0) == 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 9, a2, a2 + 9) == (i <=> 7));
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 7, a2, a2 + 7) == 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 8, a2, a2 + 7) > 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 7, a2, a2 + 8) < 0);
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool
test02(unsigned char i)
{
	unsigned char a1[] = { 0, 1, 2, 3, 4, 5, 6, i, 8 };
	unsigned char a2[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 0, a2, a2 + 0) == 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 9, a2, a2 + 9) == (i <=> 7));
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 7, a2, a2 + 7) == 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 8, a2, a2 + 7) > 0);
	VERIFY(hamon::lexicographical_compare_three_way(a1, a1 + 7, a2, a2 + 8) < 0);
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool
test03()
{
	unsigned char* p = nullptr;
	unsigned char a[] = { 1, 2 };
	VERIFY(hamon::lexicographical_compare_three_way(p, p, a, a + 2) < 0);
	VERIFY(hamon::lexicographical_compare_three_way(a, a + 2, p, p) > 0);
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, LexicographicalCompareThreeWayTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01(0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01(6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01(7));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01(8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01(999));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02(0));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02(6));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02(7));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02(8));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02(123));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		int arr1[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		int arr2[] = { 0, 1, 2, 3, 4, 5, 6, 777 };
		{
			test_container<int, input_iterator_wrapper> c1(arr1);
			test_container<int, input_iterator_wrapper> c2(arr2);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) < 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) > 0);
		}
		{
			test_container<int, input_iterator_wrapper> c1(arr1, arr1 + 6);
			test_container<int, input_iterator_wrapper> c2(arr2, arr2 + 6);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) == 0);
		}
		{
			test_container<int, input_iterator_wrapper> c1(arr1);
			test_container<int, input_iterator_wrapper> c2(arr2, arr2 + 7);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) > 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) < 0);
		}
		{
			test_container<int, input_iterator_wrapper>   c1(arr1);
			test_container<int, forward_iterator_wrapper> c2(arr2);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) < 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) > 0);
		}
		{
			test_container<int, input_iterator_wrapper>   c1(arr1);
			test_container<int, forward_iterator_wrapper> c2(arr2, arr2 + 7);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c2.begin(), c2.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) > 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) < 0);
		}
		{
			test_container<int, forward_iterator_wrapper> c1(arr1, arr1 + 7);
			test_container<int, input_iterator_wrapper>   c2(arr2);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c1.begin(), c1.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c2.begin(), c2.end()) == 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c1.begin(), c1.end(),
				c2.begin(), c2.end()) < 0);
			EXPECT_TRUE(hamon::lexicographical_compare_three_way(
				c2.begin(), c2.end(),
				c1.begin(), c1.end()) > 0);
		}
	}
	{
		std::array<unsigned char, 8> c1 = { 0, 1, 2, 3, 4, 5, 6, 7 };
		std::array<unsigned char, 8> c2 = { 0, 1, 2, 3, 4, 5, 6, 77 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c1.begin(), c1.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c2.begin(), c2.end()) == 0);

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c2.begin(), c2.end()) < 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c1.begin(), c1.end()) > 0);

		std::array<unsigned char, 7> c3 = { 0, 1, 2, 3, 4, 5, 6 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c3.begin(), c3.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c3.begin(), c3.end()) > 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c1.begin(), c1.end()) < 0);
	}
	{
		std::vector<int> c1 = { 1, 2, 3, 4, 5, 6, 7 };
		std::vector<int> c2 = { 1, 2, 3, 4, 5, 6, 77 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c1.begin(), c1.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c2.begin(), c2.end()) == 0);

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c2.begin(), c2.end()) < 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c1.begin(), c1.end()) > 0);

		std::vector<int> c3 = { 1, 2, 3, 4, 5, 6 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c3.begin(), c3.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c3.begin(), c3.end()) > 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c1.begin(), c1.end()) < 0);
	}
	{
		std::list<int>   c1 = { 0, 1, 2, 3, 4, 5, 6, 7 };
		std::vector<int> c2 = { 0, 1, 2, 3, 4, 5, 6, 77 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c1.begin(), c1.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c2.begin(), c2.end()) == 0);

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c2.begin(), c2.end()) < 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c2.begin(), c2.end(),
			c1.begin(), c1.end()) > 0);

		std::forward_list<int> c3 = { 0, 1, 2, 3, 4, 5, 6 };

		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c3.begin(), c3.end()) == 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c1.begin(), c1.end(),
			c3.begin(), c3.end()) > 0);
		EXPECT_TRUE(hamon::lexicographical_compare_three_way(
			c3.begin(), c3.end(),
			c1.begin(), c1.end()) < 0);
	}
}

}	// namespace lexicographical_compare_three_way_test

}	// namespace hamon_algorithm_test

#endif
