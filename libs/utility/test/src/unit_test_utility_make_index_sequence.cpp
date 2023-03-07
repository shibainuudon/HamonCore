/**
 *	@file	unit_test_utility_make_index_sequence.cpp
 *
 *	@brief	make_index_sequence のテスト
 */

#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace make_index_sequence_test
{

void MakeIndexSequenceTestSub(void)
{
}

void MakeIndexSequenceTestSub(hamon::size_t a)
{
	EXPECT_EQ(0u, a);
}

void MakeIndexSequenceTestSub(
	hamon::size_t a,
	hamon::size_t b,
	hamon::size_t c,
	hamon::size_t d,
	hamon::size_t e,
	hamon::size_t f,
	hamon::size_t g,
	hamon::size_t h,
	hamon::size_t i,
	hamon::size_t j)
{
	EXPECT_EQ(0u, a);
	EXPECT_EQ(1u, b);
	EXPECT_EQ(2u, c);
	EXPECT_EQ(3u, d);
	EXPECT_EQ(4u, e);
	EXPECT_EQ(5u, f);
	EXPECT_EQ(6u, g);
	EXPECT_EQ(7u, h);
	EXPECT_EQ(8u, i);
	EXPECT_EQ(9u, j);
}

template <hamon::size_t ... Seq>
void MakeIndexSequenceTest(hamon::index_sequence<Seq ...>)
{
	MakeIndexSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, MakeIndexSequenceTest)
{
	{
		using seq = hamon::make_index_sequence<0>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = hamon::make_index_sequence<1>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = hamon::make_index_sequence<10>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 10);
		MakeIndexSequenceTest(seq());
	}
	{
		using seq = hamon::make_index_sequence<100>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 100);
	}
}

}	// namespace make_index_sequence_test

}	// namespace hamon_utility_test
