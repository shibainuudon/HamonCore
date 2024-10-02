/**
 *	@file	unit_test_algorithm_ranges_fold_left.cpp
 *
 *	@brief	ranges::fold_left のテスト
 */

#include <hamon/algorithm/ranges/fold_left.hpp>
#include <hamon/functional/ranges/plus.hpp>
#include <hamon/functional/ranges/multiplies.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/array.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_fold_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::end(x), 0, ranges::plus{}) == 15);
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::end(x), 1, ranges::multiplies{}) == 120);
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::begin(x), 0, ranges::plus{}) == 0);
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::begin(x), 1, ranges::multiplies{}) == 1);
	}
	{
		hamon::array<int, 8> x = { 8,7,6,5,4,3,2,1 };
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::end(x), 0, ranges::plus{}) == 36);
		VERIFY(ranges::fold_left(ranges::begin(x), ranges::end(x), 1, ranges::multiplies{}) == 40320);
	}

	return true;
}

template <template <typename> class RangeWrapper>
inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		RangeWrapper<int> rx(x);
		VERIFY(ranges::fold_left(rx, 0, ranges::plus{}) == 15);
		VERIFY(ranges::fold_left(rx, 1, ranges::multiplies{}) == 120);
	}
	{
		int x[] = { 8,7,6,5,4,3,2,1 };
		RangeWrapper<int> rx(x);
		VERIFY(ranges::fold_left(rx, 0, ranges::plus{}) == 36);
		VERIFY(ranges::fold_left(rx, 1, ranges::multiplies{}) == 40320);
	}

	return true;
}

inline bool test03()
{
	namespace ranges = hamon::ranges;

	{
		hamon::vector<hamon::string> x
		{
			"A", "B", "C", "D",
		};
		VERIFY(
			ranges::fold_left(x, "!",
				[](hamon::string const& a, hamon::string const& b) { return "(" + a + "+" + b + ")"; }) ==
			"((((!+A)+B)+C)+D)");
	}

	return true;
}

struct S
{
	int i;
};

struct Add
{
	HAMON_CXX11_CONSTEXPR S
	operator()(S const& lhs, S const& rhs) const
	{
		return S{lhs.i + rhs.i};
	}
};

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;

	S const a[] {{1},{2},{3},{4}};
	{
		auto b = ranges::fold_left(ranges::begin(a), ranges::end(a), {0}, Add{});
		VERIFY(b.i == 10);
	}
	{
		auto b = ranges::fold_left(ranges::begin(a), ranges::end(a), {42}, Add{});
		VERIFY(b.i == 52);
	}
	{
		auto b = ranges::fold_left(a, {0}, Add{});
		VERIFY(b.i == 10);
	}
	{
		auto b = ranges::fold_left(a, {42}, Add{});
		VERIFY(b.i == 52);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFoldLeftTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_contiguous_range>());
	EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace ranges_fold_left_test

}	// namespace hamon_algorithm_test
