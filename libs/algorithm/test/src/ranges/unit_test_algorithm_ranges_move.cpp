/**
 *	@file	unit_test_algorithm_ranges_move.cpp
 *
 *	@brief	ranges::move のテスト
 */

#include <hamon/algorithm/ranges/move.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/algorithm/ranges/count.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/views/subrange.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X
{
	int i;
	int moved = 0;

	HAMON_CXX14_CONSTEXPR X() : i(0) { }
	HAMON_CXX14_CONSTEXPR X(int a) : i(a) { }

	HAMON_CXX14_CONSTEXPR X(const X&) = delete;
	HAMON_CXX14_CONSTEXPR X& operator=(const X&) = delete;

	HAMON_CXX14_CONSTEXPR X(X&& other)
		: i(other.i)
	{
		*this = hamon::move(other);
	}

	HAMON_CXX14_CONSTEXPR X& operator=(X&& other)
	{
		other.moved++;
		i = other.i;
		return *this;
	}

	friend HAMON_CXX14_CONSTEXPR bool
	operator==(const X& a, const X& b)
	{
		return a.i == b.i;
	}

	friend HAMON_CXX14_CONSTEXPR bool
	operator!=(const X& a, const X& b)
	{
		return !(a == b);
	}
};

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;
	{
		X x[7] = { 1, 2, 3, 4, 5, 6, 7 };
		X y[7] = { 0, 0, 0, 0, 0, 0, 0 };
		X z[7] = { 1, 2, 3, 4, 5, 6, 7 };
		auto res = ranges::move(x, y);
		VERIFY(res.in == x+7);
		VERIFY(res.out == y+7);
		VERIFY(ranges::equal(x, y));
		VERIFY(ranges::equal(x, z));
	}
	{
		char x[3] = { 1, 2, 3 };
		int  y[4] = { 0 };
		int  z[3] = { 1, 2, 3 };
		test_container<char, forward_iterator_wrapper<char>> cx(x);
		test_container<int, forward_iterator_wrapper<int>> cy(y);
		auto res = ranges::move(cx, cy.begin());
		VERIFY(res.in.m_ptr == x+3);
		VERIFY(res.out.m_ptr == y+3);
		VERIFY(ranges::equal(x, x+3, y, y+3));
		VERIFY(ranges::equal(x, z));
	}
	{
		char x[3] = { 1, 2, 3 };
		int  y[4] = { 0 };
		int  z[3] = { 1, 2, 3 };
		test_input_range<char> cx(x);
		test_output_range<int> cy(y);
		auto res = ranges::move(cx, ranges::begin(cy));
		VERIFY(res.in.m_ptr == x+3);
		VERIFY(res.out.m_ptr == y+3);
		VERIFY(ranges::equal(x, x+3, y, y+3));
		VERIFY(ranges::equal(x, z));
	}
	return true;
}

inline bool test02()
{
	namespace ranges = hamon::ranges;
	{
		std::vector<char> x = { 1, 2, 3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::move(x, ranges::begin(y));
		VERIFY(res.in == x.begin()+3);
		VERIFY(res.out == y.begin()+3);
		VERIFY(ranges::equal(x, z));
		VERIFY(ranges::equal(y, z));
	}
	{
		std::vector<int> x = { 1, 2, 3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::move(x, ranges::begin(y));
		VERIFY(res.in == x.begin()+3);
		VERIFY(res.out == y.begin()+3);
		VERIFY(ranges::equal(x, z));
		VERIFY(ranges::equal(y, z));
	}
	{
		std::vector<int> x = { 1, 2, 3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::move(
			hamon::make_reverse_iterator(x.end()),
			hamon::make_reverse_iterator(x.begin()),
			hamon::make_reverse_iterator(y.end()));
#if !defined(HAMON_STDLIB_LIBSTDCPP3)
		// libstdc++のranges::moveのバグでres.inに正しい値が帰ってこない
		VERIFY(res.in.base() == x.begin());
#endif
		VERIFY(res.out.base() == y.begin());
		VERIFY(ranges::equal(x, z));
		VERIFY(ranges::equal(y, z));
	}
	{
		std::vector<char> x = { 1, 2, 3 };
		std::vector<int> y(3);
		const int z[3] = { 1, 2, 3 };
		auto res = ranges::move(
			hamon::make_reverse_iterator(x.end()),
			hamon::make_reverse_iterator(x.begin()),
			hamon::make_reverse_iterator(y.end()));
#if !defined(HAMON_STDLIB_LIBSTDCPP3)
		// libstdc++のranges::moveのバグでres.inに正しい値が帰ってこない
		VERIFY(res.in.base() == x.begin());
#endif
		VERIFY(res.out.base() == y.begin());
		VERIFY(ranges::equal(x, z));
		VERIFY(ranges::equal(y, z));
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10} };
	X y[] = { {2}, {6}, {8}, {10}, {11}, {2} };
	X z[] = { {2}, {2}, {6}, {8}, {10} };
	auto res = ranges::move(x, y);
	VERIFY(res.in == x+5);
	VERIFY(res.out == y+5);
	VERIFY(ranges::equal(x, x+5, y, y+5));
	VERIFY(y[5].i == 2);
	VERIFY(ranges::equal(x, z));
	VERIFY(ranges::count(x, 1, &X::moved) == 5);
	VERIFY(ranges::count(y, 0, &X::moved) == 6);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;

#if 0	// TODO move_sentinel を追加する
	X x[] = { {2}, {2}, {6}, {8}, {10} };
	X y[] = { {2}, {6}, {8}, {10}, {11}, {2} };
	X z[] = { {2}, {2}, {6}, {8}, {10} };
	test_input_range<X> rx(x);
	auto res = ranges::move(
		std::move_iterator{ ranges::begin(rx) },
		std::move_sentinel{ ranges::end(rx) },
		ranges::begin(y));
	VERIFY(ranges::equal(x, x+5, y, y+5));
	VERIFY(hamon::move(res.in).base().m_ptr == x+5);
	VERIFY(res.out == y+5);
	VERIFY(y[5].i == 2);
	VERIFY(ranges::equal(x, z));
	VERIFY(ranges::count(x, 1, &X::moved) == 5);
	VERIFY(ranges::count(y, 0, &X::moved) == 6);
#endif

	return true;
}

inline void test05()
{
	volatile int i[2] = { 1, 2 };
	volatile int j[2] = { 0, 0 };
	int k[2] = { 0, 0 };

	hamon::ranges::move(i, i+2, j);
	EXPECT_TRUE(j[0] == 1);
	EXPECT_TRUE(j[1] == 2);
	hamon::ranges::move(i, i+2, k);
	EXPECT_TRUE(k[0] == 1);
	EXPECT_TRUE(k[1] == 2);
	hamon::ranges::move(k+1, k+2, i);
	EXPECT_TRUE(i[0] == 2);

	const volatile int* cj = j;
	hamon::ranges::move(cj, cj+2, i);
	EXPECT_TRUE(i[0] == 1);
	EXPECT_TRUE(i[1] == 2);
	hamon::ranges::move(cj+1, cj+2, k);
	EXPECT_TRUE(k[0] == 2);
	const int* ck = k;
	hamon::ranges::move(ck, ck+2, i);
	EXPECT_TRUE(i[0] == 2);
	EXPECT_TRUE(i[1] == 2);
}

template <typename It>
struct sentinel
{
	It it;

	friend bool operator==(It x, sentinel y)
	{
		return x == y.it;
	}
	friend bool operator!=(It x, sentinel y)
	{
		return !(x == y);
	}
	friend bool operator==(sentinel y, It x)
	{
		return x == y.it;
	}
	friend bool operator!=(sentinel y, It x)
	{
		return !(x == y);
	}
};

inline void test06()
{
	std::vector<int> v = { 1,2,3,4,5 };
	std::vector<int> w = { 0,0,0,0,0 };
	using Iter = std::vector<int>::iterator;
	using Sent = sentinel<Iter>;
	hamon::ranges::subrange<Iter, Sent> sr =
	{
		v.begin(),
		Sent{v.end()}
	};
	hamon::ranges::move(sr, w.begin());
	const int x[] = { 1, 2, 3, 4, 5 };
	EXPECT_TRUE(hamon::ranges::equal(w, x));
}

inline void test07()
{
	std::vector<int> v = { 1,2,3,4,5 };
	std::vector<int> w = { 0,0,0,0,0 };
	using Iter = hamon::reverse_iterator<std::vector<int>::iterator>;
	using Sent = sentinel<Iter>;
	hamon::ranges::subrange<Iter, Sent> sr =
	{
		Iter{v.end()},
		Sent{Iter{v.begin()}}
	};
	hamon::ranges::move(sr, Iter{ w.end() });
	const int x[] = { 1, 2, 3, 4, 5 };
	EXPECT_TRUE(hamon::ranges::equal(w, x));
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	                      EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());

	test05();
	test06();
	test07();
}

}	// namespace ranges_move_test

}	// namespace hamon_algorithm_test
