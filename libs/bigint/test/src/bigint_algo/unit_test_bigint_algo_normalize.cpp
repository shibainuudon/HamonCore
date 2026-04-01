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
#include "bigint_algo_test_helper.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_normalize_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType v, VectorType const& expected)
{
	hamon::bigint_algo::normalize(v);
	VERIFY(v == expected);
	return true;
}

#undef VERIFY

template <typename VectorType>
inline void test()
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{}, VectorType{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0}, VectorType{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1}, VectorType{1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0, 0}, VectorType{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0, 1}, VectorType{0, 1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 0}, VectorType{1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 1}, VectorType{1, 1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0, 0, 0}, VectorType{0}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 0, 0}, VectorType{1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0, 1, 0}, VectorType{0, 1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{0, 0, 1}, VectorType{0, 0, 1}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 2, 3}, VectorType{1, 2, 3}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 2, 3, 4, 0, 0, 0, 0}, VectorType{1, 2, 3, 4}));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(VectorType{1, 0, 2, 0, 0, 3, 4, 0 }, VectorType{1, 0, 2, 0, 0, 3, 4}));
}

GTEST_TEST(BigIntAlgoTest, NormalizeTest)
{
	test<hamon::vector<hamon::uint8_t>>();
	test<hamon::vector<hamon::uint16_t>>();
	test<hamon::vector<hamon::uint32_t>>();
	test<hamon::vector<hamon::uint64_t>>();

	test<hamon::inplace_vector<hamon::uint8_t, 10>>();
	test<hamon::inplace_vector<hamon::uint16_t, 32>>();
	test<hamon::inplace_vector<hamon::uint32_t, 100>>();
	test<hamon::inplace_vector<hamon::uint64_t, 1024>>();

	test<MyVector<hamon::uint8_t, 10>>();
	test<MyVector<hamon::uint16_t, 32>>();
	test<MyVector<hamon::uint32_t, 100>>();
	test<MyVector<hamon::uint64_t, 1024>>();
}

}	// namespace bigint_algo_normalize_test

}	// namespace hamon_bigint_test
