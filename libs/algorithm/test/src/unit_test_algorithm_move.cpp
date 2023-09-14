/**
 *	@file	unit_test_algorithm_move.cpp
 *
 *	@brief	move のテスト
 */

#include <hamon/algorithm/move.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <iterator>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace move_test
{

struct noncopyable
{
public:
	HAMON_CXX14_CONSTEXPR noncopyable()
		: value(0)
	{}

	HAMON_CXX14_CONSTEXPR noncopyable(int v)
		: value(v)
	{
	}

	HAMON_CXX14_CONSTEXPR noncopyable(noncopyable&& rhs) noexcept
		: value(hamon::move(rhs.value))
	{
		rhs.value = -1;
	}
	
	HAMON_CXX14_CONSTEXPR noncopyable& operator=(noncopyable&& rhs) noexcept
	{
		value = hamon::move(rhs.value);
		rhs.value = -1;
		return *this;
	}

	HAMON_CXX14_CONSTEXPR int get() const { return value; }

private:
	noncopyable(noncopyable const&) = delete;
	noncopyable& operator=(noncopyable const&) = delete;

	int value;
};

inline HAMON_CXX14_CONSTEXPR bool move_test()
{
	{
		int a1[] = { 10, 20, 30, 40, 50 };

		int a2[5] {};

		auto it = hamon::move(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));

		if (!(10 == a2[0])) { return false; }
		if (!(20 == a2[1])) { return false; }
		if (!(30 == a2[2])) { return false; }
		if (!(40 == a2[3])) { return false; }
		if (!(50 == a2[4])) { return false; }
		if (!(it == hamon::end(a2))) { return false; }
	}
	{
		noncopyable a1[] =
		{
			noncopyable(1),
			noncopyable(2),
			noncopyable(3),
		};

		noncopyable a2[3] {};

		auto it = hamon::move(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));

		if (!(-1 == a1[0].get())) { return false; }
		if (!(-1 == a1[1].get())) { return false; }
		if (!(-1 == a1[2].get())) { return false; }
		if (!( 1 == a2[0].get())) { return false; }
		if (!( 2 == a2[1].get())) { return false; }
		if (!( 3 == a2[2].get())) { return false; }
		if (!(it == hamon::end(a2))) { return false; }
	}
	return true;
}

GTEST_TEST(AlgorithmTest, MoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(move_test());

	{
		hamon::array<noncopyable, 4> a1 =
		{{
			noncopyable(4),
			noncopyable(5),
			noncopyable(6),
			noncopyable(7),
		}};

		noncopyable a2[5];

		auto it = hamon::move(hamon::begin(a1), hamon::end(a1), hamon::begin(a2));

		EXPECT_EQ(4, a2[0].get());
		EXPECT_EQ(5, a2[1].get());
		EXPECT_EQ(6, a2[2].get());
		EXPECT_EQ(7, a2[3].get());
		EXPECT_EQ(0, a2[4].get());
		EXPECT_TRUE(it == hamon::begin(a2) + 4);
	}
	{
		hamon::vector<noncopyable> v;
		v.emplace_back(noncopyable(5));
		v.emplace_back(noncopyable(6));
		v.emplace_back(noncopyable(7));
		v.emplace_back(noncopyable(8));
		v.emplace_back(noncopyable(9));

		hamon::list<noncopyable> l;

		hamon::move(hamon::begin(v), hamon::end(v), std::back_inserter(l));

		auto it = l.begin();
		EXPECT_EQ(5, (*it++).get());
		EXPECT_EQ(6, (*it++).get());
		EXPECT_EQ(7, (*it++).get());
		EXPECT_EQ(8, (*it++).get());
		EXPECT_EQ(9, (*it++).get());
		EXPECT_TRUE(it == l.end());
	}
}

}	// namespace move_test

}	// namespace hamon_algorithm_test
