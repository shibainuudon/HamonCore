/**
 *	@file	unit_test_algorithm_transform.cpp
 *
 *	@brief	transform のテスト
 */

#include <hamon/algorithm/transform.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace transform_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Doubling
{
	template <typename T>
	HAMON_CONSTEXPR T operator()(T x) const
	{
		return x * 2;
	}
};

HAMON_CONSTEXPR int to_int(float f)
{
	return static_cast<int>(f);
}

inline HAMON_CXX14_CONSTEXPR bool TransformTest1()
{
	{
		const int a1[] {0,1,2};
		int a2[3]{};
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), hamon::begin(a2), Doubling());

		VERIFY(0 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(4 == a2[2]);

		VERIFY(it == hamon::end(a2));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool TransformTest2()
{
	{
		const hamon::array<int, 3> a1 {{0,1,2}};
		hamon::array<int, 3> a2{};
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), hamon::begin(a2), Doubling());

		VERIFY(0 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(4 == a2[2]);

		VERIFY(it == hamon::end(a2));
	}
	return true;
}

GTEST_TEST(AlgorithmTest, TransformTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(TransformTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(TransformTest2());

// Unary Operator

	// int[3] => int[3]
	{
		const int a1[] {0,1,2};
		int a2[3];
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), hamon::begin(a2), Doubling());

		EXPECT_EQ(0, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(4, a2[2]);

		EXPECT_TRUE(it == hamon::end(a2));
	}
	// int[3] => int[3] (self assign)
	{
		int a1[] {0,1,2};
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), hamon::begin(a1), Doubling());

		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(2, a1[1]);
		EXPECT_EQ(4, a1[2]);

		EXPECT_TRUE(it == hamon::end(a1));
	}
	// array => array
	{
		const hamon::array<int, 3> a1 {{0,1,2}};
		hamon::array<int, 3> a2;
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), hamon::begin(a2), Doubling());

		EXPECT_EQ(0, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(4, a2[2]);

		EXPECT_TRUE(it == hamon::end(a2));
	}
	// vector => array
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		hamon::array<int, 3> a1;
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1), hamon::begin(a1), Doubling());

		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(4, a1[1]);
		EXPECT_EQ(6, a1[2]);

		EXPECT_TRUE(it == hamon::end(a1));
	}
	// vector => int[4]
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		int a1[4]{};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1), hamon::begin(a1), Doubling());

		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(4, a1[1]);
		EXPECT_EQ(6, a1[2]);
		EXPECT_EQ(0, a1[3]);

		EXPECT_TRUE(it == hamon::begin(a1) + 3);
	}
	// vector => vector
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		hamon::vector<int> v2 { 10, 11, 12, 13, 14 };
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1), hamon::begin(v2), Doubling());

		EXPECT_EQ( 2, v2[0]);
		EXPECT_EQ( 4, v2[1]);
		EXPECT_EQ( 6, v2[2]);
		EXPECT_EQ(13, v2[3]);
		EXPECT_EQ(14, v2[4]);

		EXPECT_TRUE(it == hamon::begin(v2) + 3);
	}
	// vector => vector (back_inserter)
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		hamon::vector<int> v2;
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1), std::back_inserter(v2), Doubling());

		EXPECT_EQ( 3u, v2.size());
		EXPECT_EQ( 2, v2[0]);
		EXPECT_EQ( 4, v2[1]);
		EXPECT_EQ( 6, v2[2]);

		(void)it;
	}
	// vector => list (back_inserter)
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(v1), hamon::end(v1), std::back_inserter(l1), Doubling());

		auto it = l1.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	// float[] => vector<int> (back_inserter)
	{
		const float a1[] {1.5, 2.5};
		hamon::vector<int> v1;
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1), std::back_inserter(v1), to_int);

		EXPECT_EQ(2u, v1.size());
		EXPECT_EQ(1, v1[0]);
		EXPECT_EQ(2, v1[1]);

		(void)it;
	}
	// float[] => list<int> (back_inserter)
	{
		const float a1[] {1.5, 2.5, 3.5};
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(a1), hamon::end(a1), std::back_inserter(l1), to_int);

		auto it = l1.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_TRUE(it == l1.end());
	}

// Binary Operator

	// vector, vector => vector
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6 };
		hamon::vector<int> v3 (3);
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2),
			hamon::begin(v3),
			hamon::plus<>());

		EXPECT_EQ(5, v3[0]);
		EXPECT_EQ(7, v3[1]);
		EXPECT_EQ(9, v3[2]);
		EXPECT_TRUE(it == hamon::end(v3));
	}
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6 };
		hamon::vector<int> v3 (3);
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2), hamon::end(v2),
			hamon::begin(v3),
			hamon::plus<>());

		EXPECT_EQ(5, v3[0]);
		EXPECT_EQ(7, v3[1]);
		EXPECT_EQ(9, v3[2]);
		EXPECT_TRUE(it == hamon::end(v3));
	}

	// vector, vector => vector (self assign)
	{
		hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6 };
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2),
			hamon::begin(v1),
			hamon::plus<>());

		EXPECT_EQ(5, v1[0]);
		EXPECT_EQ(7, v1[1]);
		EXPECT_EQ(9, v1[2]);
		EXPECT_TRUE(it == hamon::end(v1));
	}
	{
		hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6 };
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2), hamon::end(v2),
			hamon::begin(v1),
			hamon::plus<>());

		EXPECT_EQ(5, v1[0]);
		EXPECT_EQ(7, v1[1]);
		EXPECT_EQ(9, v1[2]);
		EXPECT_TRUE(it == hamon::end(v1));
	}

	// vector, vector => array
	{
		const hamon::vector<int> v1 { 1, 2, 3, 4 };
		const hamon::vector<int> v2 { 4, 5, 6 };
		hamon::array<int, 4> a1{{}};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2), hamon::end(v2),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(5, a1[0]);
		EXPECT_EQ(7, a1[1]);
		EXPECT_EQ(9, a1[2]);
		EXPECT_EQ(0, a1[3]);
		EXPECT_TRUE(it == hamon::begin(a1) + 3);
	}

	// vector, vector => int[]
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6, 7 };
		int a1[5] {};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(5, a1[0]);
		EXPECT_EQ(7, a1[1]);
		EXPECT_EQ(9, a1[2]);
		EXPECT_EQ(0, a1[3]);
		EXPECT_EQ(0, a1[4]);
		EXPECT_TRUE(it == hamon::begin(a1) + 3);
	}
	{
		const hamon::vector<int> v1 { 1, 2, 3 };
		const hamon::vector<int> v2 { 4, 5, 6, 7 };
		int a1[5] {};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2), hamon::end(v2),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(5, a1[0]);
		EXPECT_EQ(7, a1[1]);
		EXPECT_EQ(9, a1[2]);
		EXPECT_EQ(0, a1[3]);
		EXPECT_EQ(0, a1[4]);
		EXPECT_TRUE(it == hamon::begin(a1) + 3);
	}

	// vector, vector => list
	{
		const hamon::vector<int> v1 { 1, 2, 3, 4 };
		const hamon::vector<int> v2 { 4, 5, 6, 7 };
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2),
			std::back_inserter(l1),
			hamon::plus<>());

		auto it = l1.begin();
		EXPECT_EQ( 5, *it++);
		EXPECT_EQ( 7, *it++);
		EXPECT_EQ( 9, *it++);
		EXPECT_EQ(11, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	{
		const hamon::vector<int> v1 { 1, 2, 3, 4 };
		const hamon::vector<int> v2 { 4, 5, 6, 7 };
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(v2), hamon::end(v2),
			std::back_inserter(l1),
			hamon::plus<>());

		auto it = l1.begin();
		EXPECT_EQ( 5, *it++);
		EXPECT_EQ( 7, *it++);
		EXPECT_EQ( 9, *it++);
		EXPECT_EQ(11, *it++);
		EXPECT_TRUE(it == l1.end());
	}

	// vector, array  => int[]
	{
		const hamon::vector<int> v1 { 1, 2, 3, 4 };
		const hamon::array<int, 3> a1 {{ 4, 5, 6 }};
		int a2[3];
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(a1), hamon::end(a1),
			hamon::begin(a2),
			hamon::plus<>());

		EXPECT_EQ(5, a2[0]);
		EXPECT_EQ(7, a2[1]);
		EXPECT_EQ(9, a2[2]);
		EXPECT_TRUE(it == hamon::end(a2));
	}

	// list, vector => array
	{
		const hamon::list<int>   l1 { 10, 11, 12 };
		const hamon::vector<int> v1 { 13, 14, 15, 16 };
		hamon::array<int, 3> a1;
		auto const it = hamon::transform(
			hamon::begin(l1), hamon::end(l1),
			hamon::begin(v1),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(23, a1[0]);
		EXPECT_EQ(25, a1[1]);
		EXPECT_EQ(27, a1[2]);
		EXPECT_TRUE(it == hamon::end(a1));
	}
	{
		const hamon::list<int>   l1 { 10, 11, 12 };
		const hamon::vector<int> v1 { 13, 14, 15, 16 };
		hamon::array<int, 3> a1;
		auto const it = hamon::transform(
			hamon::begin(l1), hamon::end(l1),
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(23, a1[0]);
		EXPECT_EQ(25, a1[1]);
		EXPECT_EQ(27, a1[2]);
		EXPECT_TRUE(it == hamon::end(a1));
	}

	// int[], vector => list
	{
		const int a1[] = { 17, 18, 19 };
		const hamon::vector<int> v1 { 20, 21, 22 };
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(a1), hamon::end(a1),
			hamon::begin(v1),
			std::back_inserter(l1),
			hamon::plus<>());

		auto it = l1.begin();
		EXPECT_EQ(37, *it++);
		EXPECT_EQ(39, *it++);
		EXPECT_EQ(41, *it++);
		EXPECT_TRUE(it == l1.end());
	}
	{
		const int a1[] = { 17, 18, 19 };
		const hamon::vector<int> v1 { 20, 21, 22 };
		hamon::list<int> l1;
		hamon::transform(
			hamon::begin(a1), hamon::end(a1),
			hamon::begin(v1), hamon::end(v1),
			std::back_inserter(l1),
			hamon::plus<>());

		auto it = l1.begin();
		EXPECT_EQ(37, *it++);
		EXPECT_EQ(39, *it++);
		EXPECT_EQ(41, *it++);
		EXPECT_TRUE(it == l1.end());
	}

	// int[], vector => int[] (self assign)
	{
		int a1[] = { 17, 18, 19, 20 };
		const hamon::vector<int> v1 { 20, 21, 22 };
		auto const it = hamon::transform(
			hamon::begin(a1), hamon::end(a1),
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(37, a1[0]);
		EXPECT_EQ(39, a1[1]);
		EXPECT_EQ(41, a1[2]);
		EXPECT_EQ(20, a1[3]);
		EXPECT_TRUE(it == hamon::begin(a1) + 3);
	}

	// vector, array  => array (self assign)
	{
		const hamon::vector<int> v1 { 20, 21, 22 };
		hamon::array<int, 3> a1 {{23, 24, 25}};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(a1),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(43, a1[0]);
		EXPECT_EQ(45, a1[1]);
		EXPECT_EQ(47, a1[2]);
		EXPECT_TRUE(it == hamon::end(a1));
	}
	{
		const hamon::vector<int> v1 { 20, 21, 22 };
		hamon::array<int, 3> a1 {{23, 24, 25}};
		auto const it = hamon::transform(
			hamon::begin(v1), hamon::end(v1),
			hamon::begin(a1), hamon::end(a1),
			hamon::begin(a1),
			hamon::plus<>());

		EXPECT_EQ(43, a1[0]);
		EXPECT_EQ(45, a1[1]);
		EXPECT_EQ(47, a1[2]);
		EXPECT_TRUE(it == hamon::end(a1));
	}
}

#undef VERIFY

}	// namespace transform_test

}	// namespace hamon_algorithm_test
