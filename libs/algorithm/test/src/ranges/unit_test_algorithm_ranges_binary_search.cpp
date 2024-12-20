﻿/**
 *	@file	unit_test_algorithm_ranges_binary_search.cpp
 *
 *	@brief	ranges::binary_search のテスト
 */

#include <hamon/algorithm/ranges/binary_search.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/forward_list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_binary_search_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int const x[] = { 1,2,2,4,4,4 };
		test_forward_range<int const> r(x);
		VERIFY(false == ranges::binary_search(r, 0));
		VERIFY(true  == ranges::binary_search(r, 1));
		VERIFY(true  == ranges::binary_search(r, 2));
		VERIFY(false == ranges::binary_search(r, 3));
		VERIFY(true  == ranges::binary_search(r, 4));
		VERIFY(false == ranges::binary_search(r, 5));
	}
	{
		int const x[] = { 5,5,5,4,1,0 };
		test_forward_range<int const> r(x);
		auto pred = ranges::greater{};
		VERIFY(true  == ranges::binary_search(r, 0, pred));
		VERIFY(true  == ranges::binary_search(r, 1, pred));
		VERIFY(false == ranges::binary_search(r, 2, pred));
		VERIFY(false == ranges::binary_search(r, 3, pred));
		VERIFY(true  == ranges::binary_search(r, 4, pred));
		VERIFY(true  == ranges::binary_search(r, 5, pred));
	}
	return true;
}

struct X
{
	int i;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(X const& lhs, X const& rhs)
{
	return lhs.i == rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator!=(X const& lhs, X const& rhs)
{
	return lhs.i != rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator<(X const& lhs, X const& rhs)
{
	return lhs.i < rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator>(X const& lhs, X const& rhs)
{
	return lhs.i > rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator<=(X const& lhs, X const& rhs)
{
	return lhs.i <= rhs.i;
}
inline HAMON_CXX11_CONSTEXPR bool
operator>=(X const& lhs, X const& rhs)
{
	return lhs.i >= rhs.i;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		X const x[] = { {0},{1},{3},{3},{5} };
		VERIFY(true  == ranges::binary_search(x, 0, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 1, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 2, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 3, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 4, {}, &X::i));
		VERIFY(true  == ranges::binary_search(x, 5, {}, &X::i));
		VERIFY(false == ranges::binary_search(x, 6, {}, &X::i));
	}
	{
		X const x[] = { {8},{8},{6},{4},{4} };
		auto pred = ranges::greater{};
		VERIFY(false == ranges::binary_search(x, 9, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 8, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 7, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 6, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 5, pred, &X::i));
		VERIFY(true  == ranges::binary_search(x, 4, pred, &X::i));
		VERIFY(false == ranges::binary_search(x, 3, pred, &X::i));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;
	{
		X const x[] { {1},{1},{2},{3},{3},{3}, };
		VERIFY( (ranges::binary_search(ranges::begin(x), ranges::end(x), {1})));
		VERIFY( (ranges::binary_search(ranges::begin(x), ranges::end(x), {2})));
		VERIFY( (ranges::binary_search(ranges::begin(x), ranges::end(x), {3})));
		VERIFY(!(ranges::binary_search(ranges::begin(x), ranges::end(x), {0})));
		VERIFY(!(ranges::binary_search(ranges::begin(x), ranges::end(x), {4})));
		VERIFY( (ranges::binary_search(x, {1})));
		VERIFY( (ranges::binary_search(x, {2})));
		VERIFY( (ranges::binary_search(x, {3})));
		VERIFY(!(ranges::binary_search(x, {0})));
		VERIFY(!(ranges::binary_search(x, {4})));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesBinarySearchTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test02());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());

	{
		hamon::forward_list<int> x {};
		EXPECT_TRUE(false == hamon::ranges::binary_search(x, 0));
	}
}

}	// namespace ranges_binary_search_test

}	// namespace hamon_algorithm_test
