/**
 *	@file	unit_test_utility_index_sequence.cpp
 *
 *	@brief	index_sequence のテスト
 */

#include <hamon/utility/index_sequence.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace index_sequence_test
{

void IndexSequenceTestSub()
{
}

void IndexSequenceTestSub(hamon::size_t a)
{
	EXPECT_EQ(20u, a);
}

void IndexSequenceTestSub(
	hamon::size_t a,
	hamon::size_t b,
	hamon::size_t c,
	hamon::size_t d,
	hamon::size_t e,
	hamon::size_t f)
{
	EXPECT_EQ(1u, a);
	EXPECT_EQ(1u, b);
	EXPECT_EQ(2u, c);
	EXPECT_EQ(3u, d);
	EXPECT_EQ(5u, e);
	EXPECT_EQ(8u, f);
}

template <hamon::size_t ... Seq>
void IndexSequenceTest(hamon::index_sequence<Seq ...>)
{
	IndexSequenceTestSub(Seq...);
}

GTEST_TEST(UtilityTest, IndexSequenceTest)
{
	{
		using seq = hamon::index_sequence<>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 0);
		IndexSequenceTest(seq());
	}
	{
		using seq = hamon::index_sequence<20>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 1);
		IndexSequenceTest(seq());
	}
	{
		using seq = hamon::index_sequence<1, 1, 2, 3, 5, 8>;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(seq().size() == 6);
		IndexSequenceTest(seq());
	}
}

}	// namespace index_sequence_test

}	// namespace hamon_utility_test
