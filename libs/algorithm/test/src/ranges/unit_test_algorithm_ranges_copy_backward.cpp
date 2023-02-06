/**
 *	@file	unit_test_algorithm_ranges_copy_backward.cpp
 *
 *	@brief	ranges::copy_backward のテスト
 */

#include <hamon/algorithm/ranges/copy_backward.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_copy_backward_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template<typename It>
struct sentinel
{
	It it;

	friend bool operator==(It x, sentinel y)
	{
		return x == y.it;
	}
};

inline bool test01()
{
	namespace ranges = hamon::ranges;

	volatile int i[2] = { 1, 2 };
	volatile int j[2] = { 0, 0 };
	int k[2] = { 0, 0 };

	ranges::copy_backward(i, i + 2, j + 2);
	VERIFY(j[0] == 1 && j[1] == 2);
	ranges::copy_backward(i, i + 2, k + 2);
	VERIFY(k[0] == 1 && k[1] == 2);
	ranges::copy_backward(k + 1, k + 2, i + 1);
	VERIFY(i[0] == 2);

	const volatile int* cj = j;
	ranges::copy_backward(cj, cj + 2, i + 2);
	VERIFY(i[0] == 1 && i[1] == 2);
	ranges::copy_backward(cj + 1, cj + 2, k + 1);
	VERIFY(k[0] == 2);
	const int* ck = k;
	ranges::copy_backward(ck, ck + 2, i + 2);
	VERIFY(i[0] == 2 && i[1] == 2);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

#if 0
	std::vector<int> v = { 1,2,3,4,5 }, w = { 0,0,0,0,0 };
	ranges::subrange sr = { v.begin(), sentinel{v.end()} };
	ranges::copy_backward(sr, w.end());

	VERIFY(ranges::equal(w, (int[]) { 1, 2, 3, 4, 5 }));
#endif

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;

#if 0
	using std::reverse_iterator;
	std::vector<int> v = { 1,2,3,4,5 }, w = { 0,0,0,0,0 };
	ranges::subrange sr = { reverse_iterator{v.end()}, sentinel{reverse_iterator{v.begin()}} };
	ranges::copy_backward(sr, reverse_iterator{ w.begin() });
	VERIFY(ranges::equal(w, (int[]) { 1, 2, 3, 4, 5 }));
#endif

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;

	int x[7] = { 1, 2, 3, 4, 5, 6, 7 };
	int y[7] = { 0 };
	int z[7] = { 1, 2, 3, 4, 5, 6, 7 };
	auto res = ranges::copy_backward(x, ranges::end(y));
	VERIFY(res.in == x + 7);
	VERIFY(res.out == y);
	VERIFY(ranges::equal(x, y));
	VERIFY(ranges::equal(x, z));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test05()
{
	namespace ranges = hamon::ranges;

	{
		int x[7] = { 1, 2, 3, 4, 5, 6, 7 };
		int y[7] = { 0 };
		int z[7] = { 1, 2, 3, 4, 5, 6, 7 };
		auto res = ranges::copy_backward(x, ranges::end(y));
		VERIFY(res.in == x + 7);
		VERIFY(res.out == y);
		VERIFY(ranges::equal(x, y));
		VERIFY(ranges::equal(x, z));
	}
	{
		char x[3] = { 1, 2, 3 };
		int y[4] = { 0 };
		int z[3] = { 1, 2, 3 };
		test_container<char, bidirectional_iterator_wrapper<char>> cx(x);
		test_container<int, bidirectional_iterator_wrapper<int>> cy(y);
		auto res = ranges::copy_backward(cx, ranges::end(cy));
		VERIFY(res.in.m_ptr == x + 3);
		VERIFY(res.out.m_ptr == y + 1);
		VERIFY(ranges::equal(x, x + 3, y + 1, y + 4));
		VERIFY(ranges::equal(x, z));
	}

	return true;
}

inline bool test06()
{
	namespace ranges = hamon::ranges;

	{
		std::vector<char> x = { 1,2,3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::copy_backward(x, ranges::end(y));
		VERIFY(res.in == x.begin() + 3);
		VERIFY(res.out == y.begin());
		VERIFY(ranges::equal(y, z));
		VERIFY(ranges::equal(x, z));
	}
	{
		std::vector<int> x = { 1,2,3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::copy_backward(x, ranges::end(y));
		VERIFY(res.in == x.begin() + 3);
		VERIFY(res.out == y.begin());
		VERIFY(ranges::equal(y, z));
		VERIFY(ranges::equal(x, z));
	}
	{
		std::vector<int> x = { 1,2,3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::copy_backward(
			hamon::make_reverse_iterator(x.end()),
			hamon::make_reverse_iterator(x.begin()),
			hamon::make_reverse_iterator(y.begin()));
//		VERIFY(res.in.base() == x.begin());
		VERIFY(res.out.base() == y.begin() + 3);
		VERIFY(ranges::equal(y, z));
		VERIFY(ranges::equal(x, z));
	}
	{
		std::vector<char> x = { 1,2,3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::copy_backward(
			hamon::make_reverse_iterator(x.end()),
			hamon::make_reverse_iterator(x.begin()),
			hamon::make_reverse_iterator(y.begin()));
//		VERIFY(res.in.base() == x.begin());
		VERIFY(res.out.base() == y.begin() + 3);
		VERIFY(ranges::equal(y, z));
		VERIFY(ranges::equal(x, z));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test07()
{
	namespace ranges = hamon::ranges;

	int x[] = { 2, 2, 6,  8, 10 };
	int y[] = { 2, 6, 8, 10, 11, 2 };
	const int z[] = { 2, 2, 6, 8, 10 };
	auto res = ranges::copy_backward(x, ranges::end(y));
	VERIFY(ranges::equal(x, x + 5, y + 1, y + 6));
	VERIFY(res.in == x + 5);
	VERIFY(res.out == y + 1);
	VERIFY(y[0] == 2);
	VERIFY(ranges::equal(x, z));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCopyBackwardTest)
{
	                      EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	                      EXPECT_TRUE(test06());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test07());
}

}	// namespace ranges_copy_backward_test

}	// namespace hamon_algorithm_test
