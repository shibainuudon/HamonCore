/**
 *	@file	unit_test_algorithm_ranges_nth_element.cpp
 *
 *	@brief	ranges::nth_element のテスト
 */

#include <hamon/algorithm/ranges/nth_element.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/functional/identity.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_nth_element_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Iter, typename Sent, typename Comp, typename Proj>
HAMON_CXX14_CONSTEXPR bool NthElementTest(
	Iter first,
	Iter nth,
	Sent last,
	Comp comp,
	Proj proj)
{
	for (auto i = first; i != nth; ++i)
	{
		for (auto j = nth; j != last; ++j)
		{
			VERIFY(!hamon::invoke(comp,
				hamon::invoke(proj, *j),
				hamon::invoke(proj, *i)));
		}
	}

	return true;
}

template <
	typename Range,
	typename Iter,
	typename Comp = hamon::ranges::less,
	typename Proj = hamon::identity
>
HAMON_CXX14_CONSTEXPR bool NthElementTest(
	Range&& r,
	Iter nth,
	Comp comp = {},
	Proj proj = {})
{
	return NthElementTest(
		hamon::ranges::begin(r),
		nth,
		hamon::ranges::end(r),
		comp,
		proj);
}

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	for (int i = 0; i < 10; ++i)
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		auto nth = ranges::next(a, i);
		auto it = ranges::nth_element(a, nth);
		VERIFY(it == ranges::end(a));
		VERIFY(NthElementTest(a, nth));
	}
	for (int i = 0; i < 10; ++i)
	{
		int a[] { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3 };
		test_random_access_range<int> r(a);
		auto nth = ranges::next(r.begin(), i);
		auto it = ranges::nth_element(r, nth, ranges::greater{});
		VERIFY(it == ranges::end(r));
		VERIFY(NthElementTest(r, nth, ranges::greater{}));
	}
	return true;
}

struct X
{
	int i;
};

inline bool test02()
{
	namespace ranges = hamon::ranges;
	for (int i = 0; i < 5; ++i)
	{
		X a[] { {5},{1},{3},{2},{4} };
		auto nth = ranges::next(a, i);
		auto it = ranges::nth_element(a, nth, {}, &X::i);
		VERIFY(it == ranges::end(a));
		VERIFY(NthElementTest(a, nth, {}, &X::i));
	}

	{
		hamon::vector<int> a = {};
		auto it = ranges::nth_element(a, a.begin());
		VERIFY(it == a.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesNthElementTest)
{
#if defined(HAMON_MSVC) && (HAMON_MSVC < 1920)
	EXPECT_TRUE(test01());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#endif
	EXPECT_TRUE(test02());
}

}	// namespace ranges_nth_element_test

}	// namespace hamon_algorithm_test
