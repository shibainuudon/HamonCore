/**
 *	@file	unit_test_algorithm_radix_sort.cpp
 *
 *	@brief	radix_sort のテスト
 */

#include <hamon/algorithm/radix_sort.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/array.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace radix_sort_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX11_CONSTEXPR unsigned int
to_unsigned_int(float x)
{
	return static_cast<unsigned int>(x);
}

inline HAMON_CXX14_CONSTEXPR bool RadixSortTest()
{
	{
		unsigned char a[] { 3,1,4, };
		unsigned char tmp[3]{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		unsigned char b[] { 1,3,4, };
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		float a[] { 3.5f, 1.5f, 4.5f, };
		float tmp[3]{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp), to_unsigned_int);
		float b[] { 1.5f, 3.5f, 4.5f, };
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		unsigned short a[] { 1,2,2,1,2,2,2,1,1,1, };
		hamon::array<unsigned short, 10> tmp{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		unsigned short b[] { 1,1,1,1,1,2,2,2,2,2, };
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		unsigned int a[] { 3,1,4,1,5,9,2,6,5,3,5, };
		unsigned int tmp[32]{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		unsigned int b[] { 1,1,2,3,3,4,5,5,5,6,9, };
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		hamon::array<unsigned long long, 10> a {{ 19,18,17,16,15,14,13,12,11,10, }};
		unsigned long long tmp[32]{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		unsigned long long b[] { 10,11,12,13,14,15,16,17,18,19, };
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		hamon::array<unsigned int, 6> a {{ 3,1,4,1,5,9, }};
		hamon::array<unsigned int, 6> tmp{};
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		hamon::array<unsigned int, 6> b {{ 1,1,3,4,5,9, }};
		VERIFY(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RadixSortTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RadixSortTest());

	{
		std::vector<unsigned int> a { 1,4,1,4,2,1,3,5 };
		unsigned int tmp[16];
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		std::vector<unsigned int> b { 1,1,1,2,3,4,4,5 };
		EXPECT_TRUE(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		std::vector<unsigned int> a { 5,4,1,1,3, };
		std::vector<unsigned int> tmp(5);
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		std::vector<unsigned int> b { 1,1,3,4,5, };
		EXPECT_TRUE(hamon::equal(
			hamon::begin(a), hamon::end(a),
			hamon::begin(b), hamon::end(b)));
	}
	{
		std::vector<unsigned int> a;
		std::vector<unsigned int> tmp;
		hamon::radix_sort(hamon::begin(a), hamon::end(a), hamon::begin(tmp));
		EXPECT_TRUE(a.empty());
	}
}

}	// namespace radix_sort_test

}	// namespace hamon_algorithm_test
