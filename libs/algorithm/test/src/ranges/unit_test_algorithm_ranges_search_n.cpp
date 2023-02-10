﻿/**
 *	@file	unit_test_algorithm_ranges_search_n.cpp
 *
 *	@brief	ranges::search_n のテスト
 */

#include <hamon/algorithm/ranges/search_n.hpp>
#include <hamon/functional/greater.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_search_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename> class IterWrap>
inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,1,1,3,1,1,1,4,1,1,1,1 };
		test_range<int, IterWrap<int>> r(x);
		auto res = ranges::search_n(r, 0, 1);
		VERIFY(res.begin().m_ptr == x+0 && res.end().m_ptr == x+0);
		res = ranges::search_n(r, 1, 1);
		VERIFY(res.begin().m_ptr == x+0 && res.end().m_ptr == x+1);
		res = ranges::search_n(r, 2, 1);
		VERIFY(res.begin().m_ptr == x+2 && res.end().m_ptr == x+4);
		res = ranges::search_n(r, 3, 1);
		VERIFY(res.begin().m_ptr == x+5 && res.end().m_ptr == x+8);
		res = ranges::search_n(r, 4, 1);
		VERIFY(res.begin().m_ptr == x+9 && res.end().m_ptr == x+13);
		res = ranges::search_n(r, 5, 1);
		VERIFY(res.begin().m_ptr == x+13 && res.end().m_ptr == x+13);
	}
	{
		int x[] = { 1,2,1,1,3,1,1,1,4,1,1,1,1,5 };
		test_range<int, IterWrap<int>> r(x);
		auto res = ranges::search_n(r, 0, 1);
		VERIFY(res.begin().m_ptr == x+0 && res.end().m_ptr == x+0);
		res = ranges::search_n(r, 1, 1);
		VERIFY(res.begin().m_ptr == x+0 && res.end().m_ptr == x+1);
		res = ranges::search_n(r, 2, 1);
		VERIFY(res.begin().m_ptr == x+2 && res.end().m_ptr == x+4);
		res = ranges::search_n(r, 3, 1);
		VERIFY(res.begin().m_ptr == x+5 && res.end().m_ptr == x+8);
		res = ranges::search_n(r, 4, 1);
		VERIFY(res.begin().m_ptr == x+9 && res.end().m_ptr == x+13);
		res = ranges::search_n(r, 5, 1);
		VERIFY(res.begin().m_ptr == x+14 && res.end().m_ptr == x+14);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1, 2, 3, 4, 5 };
		auto res = ranges::search_n(x+0, x+5, 0, 3);
		VERIFY(res.begin() == x+0 && res.end() == x+0);
		res = ranges::search_n(x+0, x+5, 1, 3);
		VERIFY(res.begin() == x+2 && res.end() == x+3);
		res = ranges::search_n(x+0, x+5, 1, 6);
		VERIFY(res.begin() == x+5 && res.end() == x+5);
	}
	{
		int x[] = { 1, 2, 3, 4, 5, 6 };
		auto res = ranges::search_n(x, 3, 3, hamon::greater<>());
		VERIFY(res.begin() == x+3 && res.end() == x+6);
		res = ranges::search_n(x, 2, 4, hamon::greater<>());
		VERIFY(res.begin() == x+4 && res.end() == x+6);
		res = ranges::search_n(x, 1, 5, hamon::greater<>());
		VERIFY(res.begin() == x+5 && res.end() == x+6);
		res = ranges::search_n(x, 1, 6, hamon::greater<>());
		VERIFY(res.begin() == x+6 && res.end() == x+6);
	}

	return true;
}

struct X
{
	int i;
};

inline bool test03()
{
	namespace ranges = hamon::ranges;

	{
		X x[] = { {1}, {2}, {3}, {4}, {5} };
		auto res = ranges::search_n(x+0, x+5, 0, 3, {}, &X::i);
		VERIFY(res.begin() == x+0 && res.end() == x+0);
		res = ranges::search_n(x+0, x+5, 1, 3, {}, &X::i);
		VERIFY(res.begin() == x+2 && res.end() == x+3);
		res = ranges::search_n(x+0, x+5, 1, 6, {}, &X::i);
		VERIFY(res.begin() == x+5 && res.end() == x+5);
	}
	{
		X x[] = { {1}, {2}, {3}, {4}, {5}, {6} };
		auto res = ranges::search_n(x, 3, 3, hamon::greater<>(), &X::i);
		VERIFY(res.begin() == x+3 && res.end() == x+6);
		res = ranges::search_n(x, 2, 4, hamon::greater<>(), &X::i);
		VERIFY(res.begin() == x+4 && res.end() == x+6);
		res = ranges::search_n(x, 1, 5, hamon::greater<>(), &X::i);
		VERIFY(res.begin() == x+5 && res.end() == x+6);
		res = ranges::search_n(x, 1, 6, hamon::greater<>(), &X::i);
		VERIFY(res.begin() == x+6 && res.end() == x+6);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSearchNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_search_n_test

}	// namespace hamon_algorithm_test
