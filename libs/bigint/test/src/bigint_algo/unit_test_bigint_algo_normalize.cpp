/**
 *	@file	unit_test_bigint_algo_normalize.cpp
 *
 *	@brief	bigint_algo::normalize のテスト
 */

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_normalize_test
{

template <typename T>
void test()
{
	{
		hamon::vector<T> a{};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0, 1, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{0, 0, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 0, 1};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 2, 3};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 2, 3};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 2, 3, 4, 0, 0, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 2, 3, 4};
		EXPECT_EQ(a, expected);
	}
	{
		hamon::vector<T> a{1, 0, 2, 0, 0, 3, 4, 0 };
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 0, 2, 0, 0, 3, 4};
		EXPECT_EQ(a, expected);
	}
}

GTEST_TEST(BigIntAlgoTest, NormalizeTest)
{
	test<hamon::uint8_t>();
	test<hamon::uint16_t>();
	test<hamon::uint32_t>();
	test<hamon::uint64_t>();
}

}	// namespace bigint_algo_normalize_test

}	// namespace hamon_bigint_test
