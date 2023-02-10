/**
 *	@file	unit_test_algorithm_ranges_search.cpp
 *
 *	@brief	ranges::search のテスト
 */

#include <hamon/algorithm/ranges/search.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_search_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	using std::get;

	{
		int x[] = {1,2,3,4,5};
		int y[] = {3,4};
		auto res = ranges::search(x, y);
		VERIFY(
			get<0>(res) == x+2 &&
			get<1>(res) == x+4);
	}
	{
		int x[] = {1,2,3,4,5};
		int y[] = {3,4,6};
		auto res = ranges::search(x, y);
		VERIFY(
			get<0>(res) == x+5 &&
			get<1>(res) == x+5);
	}
	{
		int x[] = {1,2,3,4,5};
		int y[] = {1,3,4};
		auto res = ranges::search(x, y);
		VERIFY(
			get<0>(res) == x+5 &&
			get<1>(res) == x+5);
	}

	return true;
}

struct X { int i; };

inline bool test02()
{
	namespace ranges = hamon::ranges;
	using std::get;

	X x[] = { {2}, {6}, {8}, {10}, {11} };
	X y[] = { {10}, {11} };

	{
		test_forward_range<X> r(x);
		auto res = ranges::search(r, y, {}, &X::i, &X::i);
		VERIFY(
			(*get<0>(res)).i == 10 &&
			get<1>(res) == ranges::end(r));

		res = ranges::search(r, r, {}, &X::i, &X::i);
		VERIFY(
			get<0>(res) == ranges::begin(r) &&
			get<1>(res) == ranges::end(r));
	}

	return true;
}

inline bool test03()
{
	namespace ranges = hamon::ranges;
	using std::get;

	X x[] ={ {2}, {2}, {6}, {8}, {10}, {11} };
	X y[] ={ {6}, {8} };
	int z[] ={ 2, 8 };
	int w[] ={ 2 };

	VERIFY(get<0>(ranges::search(x, y, {}, &X::i, &X::i)) == x+2);
	VERIFY(get<1>(ranges::search(x, y, {}, &X::i, &X::i)) == x+4);

	VERIFY(get<0>(ranges::search(x, z, {}, &X::i)) == x+6);
	VERIFY(get<1>(ranges::search(x, z, {}, &X::i)) == x+6);

	VERIFY(get<0>(ranges::search(x, w, {}, &X::i)) == x+0);
	VERIFY(get<1>(ranges::search(x, w, {}, &X::i)) == x+1);

	VERIFY(get<0>(ranges::search(x, x+6, w, w, {}, &X::i)) == x+0);
	VERIFY(get<1>(ranges::search(x, x+6, w, w, {}, &X::i)) == x+0);

	VERIFY(get<0>(ranges::search(x, x, w, w+1, {}, &X::i)) == x+0);
	VERIFY(get<1>(ranges::search(x, x, w, w+1, {}, &X::i)) == x+0);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesSearchTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_search_test

}	// namespace hamon_algorithm_test
