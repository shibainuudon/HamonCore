/**
 *	@file	unit_test_algorithm_copy.cpp
 *
 *	@brief	copy のテスト
 */

#include <hamon/algorithm/copy.hpp>
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

namespace copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool CopyTestArray()
{
	// copy(first, last, result)
	{
		const int a[] { 1, 2, 3 };
		int b[3] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
	}
	{
		const unsigned int a[] { 1, 2, 3 };
		unsigned int b[5] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 3));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);
	}
	{
		char a[] { 1, 2, 3 };

		auto ret = hamon::copy(a+1, a+3, a);
		VERIFY(ret == a+2);

		VERIFY(2 == a[0]);
		VERIFY(3 == a[1]);
		VERIFY(3 == a[2]);
	}

	// copy(first, last, result_first, result_last)
	{
		const short a[] { 1, 2, 3 };
		short b[3]{};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[2]{};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
	}
	{
		const int a[] { 1, 2, 3 };
		int b[5] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 3));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool CopyTestStdArray()
{
	// copy(first, last, result)
	{
		const int a[] { 1, 2, 3 };
		hamon::array<int, 3> b {{}};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
	}
	{
		const hamon::array<int, 3> a {{ 1, 2, 3 }};
		hamon::array<int, 4> b {{}};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 3));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(0 == b[3]);
	}

	// copy(first, last, result_first, result_last)
	{
		const hamon::array<int, 3> a {{ 1, 2, 3 }};
		int b[3] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
	}
	{
		const int a[] { 1, 2, 3 };
		hamon::array<int, 5> b {{}};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::next(hamon::begin(b), 3));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
		VERIFY(3 == b[2]);
		VERIFY(0 == b[3]);
		VERIFY(0 == b[4]);
	}
	{
		const int a[] { 1, 2, 3 };
		hamon::array<int, 2> b {{}};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		VERIFY(ret == hamon::end(b));

		VERIFY(1 == b[0]);
		VERIFY(2 == b[1]);
	}

	return true;
}

GTEST_TEST(AlgorithmTest, CopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTestArray());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CopyTestStdArray());

	{
		const hamon::array<int, 4> a {{ 4, 5, 6, 7 }};
		hamon::vector<int> b(5);

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 4));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
		EXPECT_EQ(7, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const hamon::array<int, 4> a {{ 4, 5, 6, 7 }};
		hamon::vector<int> b(5);

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 4));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
		EXPECT_EQ(7, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const hamon::array<int, 4> a {{ 4, 5, 6, 7 }};
		hamon::vector<int> b(3);

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));

		EXPECT_EQ(4, b[0]);
		EXPECT_EQ(5, b[1]);
		EXPECT_EQ(6, b[2]);
	}
	{
		const hamon::vector<int> a { 5, 6, 7, 8, 9 };
		hamon::list<int> b;

		hamon::copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::vector<int> a { 5, 6, 7, 8, 9 };
		hamon::list<int> b { 1, 2, 3 };

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::vector<int> a { 5, 6, 7, 8, 9 };
		hamon::list<int> b { 1, 2, 3, 4, 5, 6, 7 };

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 5));

		auto it = b.begin();
		EXPECT_EQ(5, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_EQ(8, *it++);
		EXPECT_EQ(9, *it++);
		EXPECT_EQ(6, *it++);
		EXPECT_EQ(7, *it++);
		EXPECT_TRUE(it == b.end());
	}
	{
		const hamon::list<int> a { 1, 2, 3, 4 };
		int b[5] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 4));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
		EXPECT_EQ(4, b[3]);
		EXPECT_EQ(0, b[4]);
	}
	{
		const hamon::list<int> a { 1, 2, 3, 4 };
		int b[3] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b), hamon::end(b));
		EXPECT_TRUE(ret == hamon::end(b));

		EXPECT_EQ(1, b[0]);
		EXPECT_EQ(2, b[1]);
		EXPECT_EQ(3, b[2]);
	}
	{
		const hamon::vector<int> a;
		hamon::list<int> b;

		hamon::copy(hamon::begin(a), hamon::end(a), std::back_inserter(b));

		EXPECT_TRUE(b.empty());
	}
	{
		const hamon::list<int> a;
		int b[3] {};

		auto ret = hamon::copy(hamon::begin(a), hamon::end(a), hamon::begin(b));
		EXPECT_TRUE(ret == hamon::next(hamon::begin(b), 0));

		EXPECT_EQ(0, b[0]);
		EXPECT_EQ(0, b[1]);
		EXPECT_EQ(0, b[2]);
	}
}

#undef VERIFY

}	// namespace copy_test

}	// namespace hamon_algorithm_test
