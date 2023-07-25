/**
 *	@file	unit_test_bigint_algo_normalize.cpp
 *
 *	@brief	bigint_algo::normalize のテスト
 */

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_normalize_test
{

template <typename T>
void test()
{
	{
		std::vector<T> const a{};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0, 1};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0, 1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 1};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1, 1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0, 0, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 0, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0, 1, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0, 1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{0, 0, 1};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{0, 0, 1};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 2, 3};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1, 2, 3};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 2, 3, 4, 0, 0, 0, 0};
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1, 2, 3, 4};
		EXPECT_EQ(c, expected);
	}
	{
		std::vector<T> const a{1, 0, 2, 0, 0, 3, 4, 0 };
		auto const c = hamon::bigint_algo::normalize(a);
		std::vector<T> const expected{1, 0, 2, 0, 0, 3, 4};
		EXPECT_EQ(c, expected);
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
