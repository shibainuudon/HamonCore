﻿/**
 *	@file	unit_test_algorithm_move_backward.cpp
 *
 *	@brief	move_backward のテスト
 */

#include <hamon/algorithm/move_backward.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace move_backward_test
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

inline HAMON_CXX14_CONSTEXPR bool move_backward_test()
{
	{
		int a[] = { 10, 20, 30, 40, 50 };

		auto it = hamon::move_backward(a, a + 3, a + 5);

		if (!(10 == a[2])) { return false; }
		if (!(20 == a[3])) { return false; }
		if (!(30 == a[4])) { return false; }
		if (!(it == a + 2)) { return false; }
	}
	{
		noncopyable a[] =
		{
			noncopyable(1),
			noncopyable(2),
			noncopyable(3),
		};

		{
			auto const it = hamon::move_backward(
				hamon::begin(a),
				hamon::next(hamon::begin(a), 2),
				hamon::end(a));
			if (!(it == hamon::next(hamon::begin(a), 1))) { return false; }
		}

		if (!(-1 == a[0].get())) { return false; }
		if (!( 1 == a[1].get())) { return false; }
		if (!( 2 == a[2].get())) { return false; }
	}
	return true;
}

GTEST_TEST(AlgorithmTest, MoveBackwardTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(move_backward_test());

	{
		hamon::array<noncopyable, 4> a =
		{{
			noncopyable(9),
			noncopyable(8),
			noncopyable(7),
			noncopyable(6),
		}};

		{
			auto const it = hamon::move_backward(
				hamon::begin(a),
				hamon::next(hamon::begin(a), 3),
				hamon::end(a));
			EXPECT_TRUE(it == hamon::next(hamon::begin(a), 1));
		}

		EXPECT_EQ(-1, a[0].get());
		EXPECT_EQ( 9, a[1].get());
		EXPECT_EQ( 8, a[2].get());
		EXPECT_EQ( 7, a[3].get());
	}

	{
		std::vector<noncopyable> v;
		v.emplace_back(noncopyable(5));
		v.emplace_back(noncopyable(6));
		v.emplace_back(noncopyable(7));
		v.emplace_back(noncopyable(8));
		v.emplace_back(noncopyable(9));

		{
			auto const it = hamon::move_backward(
				hamon::begin(v),
				hamon::next(hamon::begin(v), 3),
				hamon::end(v));
			EXPECT_TRUE(it == hamon::next(hamon::begin(v), 2));
		}

		EXPECT_EQ(-1, v[0].get());
		EXPECT_EQ(-1, v[1].get());
		EXPECT_EQ( 5, v[2].get());
		EXPECT_EQ( 6, v[3].get());
		EXPECT_EQ( 7, v[4].get());
	}
	{
		std::list<noncopyable> l;
		l.emplace_back(noncopyable(0));
		l.emplace_back(noncopyable(1));
		l.emplace_back(noncopyable(2));
		l.emplace_back(noncopyable(3));
		l.emplace_back(noncopyable(4));
		l.emplace_back(noncopyable(5));

		{
			auto const it = hamon::move_backward(
				hamon::begin(l),
				hamon::next(hamon::begin(l), 2),
				hamon::end(l));
			EXPECT_TRUE(it == hamon::next(hamon::begin(l), 4));
		}

		{
			auto it = l.begin();
			EXPECT_EQ(-1, (it++)->get());
			EXPECT_EQ(-1, (it++)->get());
			EXPECT_EQ( 2, (it++)->get());
			EXPECT_EQ( 3, (it++)->get());
			EXPECT_EQ( 0, (it++)->get());
			EXPECT_EQ( 1, (it++)->get());
			EXPECT_TRUE(it == l.end());
		}
	}
}

}	// namespace move_backward_test

}	// namespace hamon_algorithm_test
