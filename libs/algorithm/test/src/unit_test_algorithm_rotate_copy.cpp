/**
 *	@file	unit_test_algorithm_rotate_copy.cpp
 *
 *	@brief	rotate_copy のテスト
 */

#include <hamon/algorithm/rotate_copy.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace rotate_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool RotateCopyTest1()
{
	{
		const int a[] { 1,2,3 };
		int b[3] {};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 1),
			hamon::end(a),
			hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 3));
		VERIFY(2 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(1 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateCopyTest2()
{
	{
		const int a[] { 42 };
		int b[3] {};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 0),
			hamon::end(a),
			hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 1));
		VERIFY(42 == b[0]);
		VERIFY( 0 == b[1]);
		VERIFY( 0 == b[2]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateCopyTest3()
{
	{
		const int a[] { 1,2,3 };
		hamon::array<int, 5> b {{}};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 2),
			hamon::end(a),
			hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 3));
		VERIFY(3 == b[0]);
		VERIFY(1 == b[1]);
		VERIFY(2 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool RotateCopyTest4()
{
	{
		const hamon::array<int, 4> a {{ 1,2,3,4 }};
		int b[4] {};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 1),
			hamon::end(a),
			hamon::begin(b));
		VERIFY(it == hamon::next(hamon::begin(b), 4));
		VERIFY(2 == b[0]);
		VERIFY(3 == b[1]);
		VERIFY(4 == b[2]);
		VERIFY(1 == b[3]);
	}
	return true;
}

GTEST_TEST(AlgorithmTest, RotateCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateCopyTest1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateCopyTest2());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateCopyTest3());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RotateCopyTest4());

	{
		const hamon::array<int, 4> a {{ 1,2,3,4 }};
		hamon::list<int> b;
		hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 4),
			hamon::end(a),
			std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(1, *it++);
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(3, *it++);
		EXPECT_EQ(4, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::vector<int> a { 1,2,3,4,5 };
		hamon::vector<int> b;
		hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 3),
			hamon::end(a),
			std::back_inserter(b));
		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(1, b[2]);
		EXPECT_EQ(2, b[3]);
		EXPECT_EQ(3, b[4]);
	}
	{
		const hamon::vector<int> a { 1,2,3,4 };
		int b[4] {};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 1),
			hamon::end(a),
			hamon::begin(b));
		EXPECT_TRUE(it == hamon::next(hamon::begin(b), 4));
		EXPECT_EQ(2, b[0]);
		EXPECT_EQ(3, b[1]);
		EXPECT_EQ(4, b[2]);
		EXPECT_EQ(1, b[3]);
	}
	{
		const hamon::vector<int> a;
		hamon::vector<int> b;
		hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 0),
			hamon::end(a),
			std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
	{
		const hamon::list<int> a { 1,2 };
		hamon::list<int> b;
		hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 1),
			hamon::end(a),
			std::back_inserter(b));
		auto it = b.begin();
		EXPECT_EQ(2, *it++);
		EXPECT_EQ(1, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::list<int> a { 1,2,3 };
		hamon::array<int, 4> b {{}};
		auto it = hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 2),
			hamon::end(a),
			hamon::begin(b));
		EXPECT_TRUE(it == hamon::next(hamon::begin(b), 3));
		EXPECT_EQ(3, b[0]);
		EXPECT_EQ(1, b[1]);
		EXPECT_EQ(2, b[2]);
		EXPECT_EQ(0, b[3]);
	}
	{
		const hamon::list<int> a;
		hamon::list<int> b;
		hamon::rotate_copy(
			hamon::begin(a),
			hamon::next(hamon::begin(a), 0),
			hamon::end(a),
			std::back_inserter(b));
		EXPECT_TRUE(b.empty());
	}
}

#undef VERIFY

}	// namespace rotate_copy_test

}	// namespace hamon_algorithm_test
