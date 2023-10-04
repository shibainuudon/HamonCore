/**
 *	@file	unit_test_algorithm_ranges_fold_left_with_iter.cpp
 *
 *	@brief	ranges::fold_left_with_iter のテスト
 */

#include <hamon/algorithm/ranges/fold_left_with_iter.hpp>
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

namespace ranges_fold_left_with_iter_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		{
			auto ret = ranges::fold_left_with_iter(ranges::begin(x), ranges::end(x), 0, ranges::plus{});
			VERIFY(ret.value == 15);
			VERIFY(ret.in == ranges::end(x));
		}
		{
			auto ret = ranges::fold_left_with_iter(ranges::begin(x), ranges::end(x), 1, ranges::multiplies{});
			VERIFY(ret.value == 120);
			VERIFY(ret.in == ranges::end(x));
		}
		{
			auto ret = ranges::fold_left_with_iter(ranges::begin(x), ranges::begin(x), 0, ranges::plus{});
			VERIFY(ret.value == 0);
			VERIFY(ret.in == ranges::begin(x));
		}
	}
	{
		hamon::array<int, 8> x = { 8,7,6,5,4,3,2,1 };
		{
			auto ret = ranges::fold_left_with_iter(ranges::begin(x), ranges::end(x), 100, ranges::plus{});
			VERIFY(ret.value == 136);
			VERIFY(ret.in == ranges::end(x));
		}
		{
			auto ret = ranges::fold_left_with_iter(ranges::begin(x), ranges::end(x), 1, ranges::multiplies{});
			VERIFY(ret.value == 40320);
			VERIFY(ret.in == ranges::end(x));
		}
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
		{
			auto ret = ranges::fold_left_with_iter(rx, 1, ranges::plus{});
			VERIFY(ret.value == 16);
			VERIFY(ret.in == ranges::end(rx));
		}
		{
			auto ret = ranges::fold_left_with_iter(rx, 2, ranges::multiplies{});
			VERIFY(ret.value == 240);
			VERIFY(ret.in == ranges::end(rx));
		}
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
		auto ret = ranges::fold_left_with_iter(x, "!",
			[](hamon::string const& a, hamon::string const& b) { return "(" + a + "+" + b + ")"; });
		VERIFY(ret.value == "((((!+A)+B)+C)+D)");
		VERIFY(ret.in == x.end());
	}
	{
		hamon::vector<hamon::string> x{};
		auto ret = ranges::fold_left_with_iter(x, "X", ranges::plus{});
		VERIFY(ret.value == "X");
		VERIFY(ret.in == x.begin());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFoldLeftWithIterTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_contiguous_range>());
	EXPECT_TRUE(test03());
}

}	// namespace ranges_fold_left_with_iter_test

}	// namespace hamon_algorithm_test
