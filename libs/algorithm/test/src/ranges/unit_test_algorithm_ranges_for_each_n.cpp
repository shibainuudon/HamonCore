/**
 *	@file	unit_test_algorithm_ranges_for_each_n.cpp
 *
 *	@brief	ranges::for_each_n のテスト
 */

#include <hamon/algorithm/ranges/for_each_n.hpp>
#include <hamon/functional/negate.hpp>
#include <hamon/functional/ref.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_for_each_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct Foo
{
	int s = 0;
	HAMON_CXX14_CONSTEXPR void operator()(int i)
	{
		s += i;
	}
};

template <template <typename> class wrapper>
inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3,4,5 };
	{
		test_range<int, wrapper> rx(x);
		Foo func{};
		auto res = ranges::for_each_n(rx.begin(), 3, hamon::ref(func));
		VERIFY(res.in.m_ptr == x+3);
		VERIFY(func.s == 1+2+3);
		res.fun(1);
		VERIFY(func.s == 1+2+3+1);
	}
	{
		test_range<int, wrapper> rx(x);
		Foo func{};
		auto res= ranges::for_each_n(rx.begin(), -1, hamon::ref(func));
		VERIFY(res.in.m_ptr == x);
		VERIFY(func.s == 0);
		res.fun(1);
		VERIFY(func.s == 1);
	}
	{
		test_range<int, wrapper> rx(x);
		Foo func{};
		auto res = ranges::for_each_n(rx.begin(), 5, hamon::ref(func), hamon::negate<>{});
		VERIFY(res.in.m_ptr == x+5);
		VERIFY(func.s == -(1+2+3+4+5));
		res.fun(-6);
		VERIFY(func.s == -(1+2+3+4+5+6));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3,4,5 };
	int p = 1;
	ranges::for_each_n(x+1, 4, [&p](int i) { p*=i; }, [](int i) { return i+1; });
	return p == 3*4*5*6;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesForEachNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<input_iterator_wrapper>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01<random_access_iterator_wrapper>());
	EXPECT_TRUE(test02());
}

}	// namespace ranges_for_each_n_test

}	// namespace hamon_algorithm_test
