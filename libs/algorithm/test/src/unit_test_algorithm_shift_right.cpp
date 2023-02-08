﻿/**
 *	@file	unit_test_algorithm_shift_right.cpp
 *
 *	@brief	shift_right のテスト
 */

#include <hamon/algorithm/shift_right.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace shift_right_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 0);
		VERIFY(ret == ranges::begin(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 1);
		VERIFY(ret == ranges::next(ranges::begin(x), 1));
//		VERIFY(x[0] == 1);	// undefined
		VERIFY(x[1] == 1);
		VERIFY(x[2] == 2);
		VERIFY(x[3] == 3);
		VERIFY(x[4] == 4);
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 2);
		VERIFY(ret == ranges::next(ranges::begin(x), 2));
//		VERIFY(x[0] == 1);	// undefined
//		VERIFY(x[1] == 2);	// undefined
		VERIFY(x[2] == 1);
		VERIFY(x[3] == 2);
		VERIFY(x[4] == 3);
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 3);
		VERIFY(ret == ranges::next(ranges::begin(x), 3));
//		VERIFY(x[0] == 1);	// undefined
//		VERIFY(x[1] == 2);	// undefined
//		VERIFY(x[2] == 3);	// undefined
		VERIFY(x[3] == 1);
		VERIFY(x[4] == 2);
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 4);
		VERIFY(ret == ranges::next(ranges::begin(x), 4));
//		VERIFY(x[0] == 1);	// undefined
//		VERIFY(x[1] == 2);	// undefined
//		VERIFY(x[2] == 3);	// undefined
//		VERIFY(x[3] == 4);	// undefined
		VERIFY(x[4] == 1);
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 5);
		VERIFY(ret == ranges::end(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		auto ret = hamon::shift_right(ranges::begin(x), ranges::end(x), 6);
		VERIFY(ret == ranges::end(x));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

template <template <typename> class IterWrap>
inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap<int>> cx(x);
		auto ret = hamon::shift_right(ranges::begin(cx), ranges::end(cx), 0);
		VERIFY(ret == ranges::begin(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap<int>> cx(x);
		auto ret = hamon::shift_right(ranges::begin(cx), ranges::end(cx), 1);
		VERIFY(ret == ranges::next(ranges::begin(cx), 1));
//		VERIFY(x[0] == 1);	// undefined
		VERIFY(x[1] == 1);
		VERIFY(x[2] == 2);
		VERIFY(x[3] == 3);
		VERIFY(x[4] == 4);
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap<int>> cx(x);
		auto ret = hamon::shift_right(ranges::begin(cx), ranges::end(cx), 4);
		VERIFY(ret == ranges::next(ranges::begin(cx), 4));
//		VERIFY(x[0] == 1);	// undefined
//		VERIFY(x[1] == 2);	// undefined
//		VERIFY(x[2] == 3);	// undefined
//		VERIFY(x[3] == 4);	// undefined
		VERIFY(x[4] == 1);
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap<int>> cx(x);
		auto ret = hamon::shift_right(ranges::begin(cx), ranges::end(cx), 5);
		VERIFY(ret == ranges::end(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	{
		int x[] = { 1,2,3,4,5 };
		test_container<int, IterWrap<int>> cx(x);
		auto ret = hamon::shift_right(ranges::begin(cx), ranges::end(cx), 6);
		VERIFY(ret == ranges::end(cx));
		int y[] = { 1,2,3,4,5 };
		VERIFY(ranges::equal(x, y));
	}
	return true;
}

struct X
{
	int a = -1;
	bool moved_from = false;

	HAMON_CXX14_CONSTEXPR X() = default;

	HAMON_CXX14_CONSTEXPR X(int b) : a(b) {}

	X(const X&) = delete;
	X& operator=(const X&) = delete;

	HAMON_CXX14_CONSTEXPR X(X&& other) noexcept
	{
		a = other.a;
		other.moved_from = true;
		moved_from = false;
	}

	HAMON_CXX14_CONSTEXPR X& operator=(X&& other) noexcept
	{
		a = other.a;
		other.moved_from = true;
		moved_from = false;
		return *this;
	}
};

template <int N, template <typename> class IterWrap>
inline HAMON_CXX14_CONSTEXPR bool test03()
{
	for (int n = 0; n < N+5; n++)
	{
		X x[N];
		for (int i = 0; i < N; i++)
		{
			x[i] = X(i);
		}

		test_container<X, IterWrap<X>> cx(x);
		auto out = hamon::shift_right(cx.begin(), cx.end(), n);
		if (n < N)
		{
			VERIFY(out.m_ptr == x+n);
			for (int i = n; i < N; i++)
			{
				VERIFY(x[i].a == i-n);
			}

			for (int i = 0; i < hamon::min(n, N-n); i++)
			{
				VERIFY(x[i].moved_from);
			}

			for (int i = hamon::min(n, N-n); i < hamon::max(n, N-n); i++)
			{
				VERIFY(!x[i].moved_from);
			}
		}
		else
		{
			VERIFY(out.m_ptr == x+N);
			for (int i = 0; i < N; i++)
			{
				VERIFY(x[i].a == i);
				VERIFY(!x[i].moved_from);
			}
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, ShiftRightTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<forward_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<bidirectional_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<random_access_iterator_wrapper>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, forward_iterator_wrapper>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, bidirectional_iterator_wrapper>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test03<23, random_access_iterator_wrapper>()));
}

}	// namespace shift_right_test

}	// namespace hamon_algorithm_test
