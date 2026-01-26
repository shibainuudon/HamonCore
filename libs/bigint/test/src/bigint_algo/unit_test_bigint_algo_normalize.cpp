/**
 *	@file	unit_test_bigint_algo_normalize.cpp
 *
 *	@brief	bigint_algo::normalize のテスト
 */

#include <hamon/bigint/bigint_algo/normalize.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_normalize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool test()
{
	// vector
	{
		hamon::vector<T> a{};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0, 1, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{0, 0, 1};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{0, 0, 1};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 2, 3};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 2, 3};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 2, 3, 4, 0, 0, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 2, 3, 4};
		VERIFY(a == expected);
	}
	{
		hamon::vector<T> a{1, 0, 2, 0, 0, 3, 4, 0 };
		hamon::bigint_algo::normalize(a);
		hamon::vector<T> const expected{1, 0, 2, 0, 0, 3, 4};
		VERIFY(a == expected);
	}

	// inplace_vector
	{
		hamon::inplace_vector<T, 8> a{1, 2, 3, 4, 0, 0, 0, 0};
		hamon::bigint_algo::normalize(a);
		hamon::inplace_vector<T, 8> const expected{1, 2, 3, 4};
		VERIFY(a == expected);
	}
	{
		hamon::inplace_vector<T, 8> a{1, 0, 2, 0, 0, 3, 4, 0 };
		hamon::bigint_algo::normalize(a);
		hamon::inplace_vector<T, 8> const expected{1, 0, 2, 0, 0, 3, 4};
		VERIFY(a == expected);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, NormalizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<hamon::uint8_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<hamon::uint16_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<hamon::uint32_t>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<hamon::uint64_t>());
}

}	// namespace bigint_algo_normalize_test

}	// namespace hamon_bigint_test
