/**
 *	@file	unit_test_algorithm_ranges_contains.cpp
 *
 *	@brief	ranges::contains のテスト
 */

#include <hamon/algorithm/ranges/contains.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/array.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <hamon/map.hpp>
#include <hamon/set.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_contains_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool Test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 2, 2, 6, 8, 10, 11 };
	{
		VERIFY(!ranges::contains(x, x+6, 1));
		VERIFY( ranges::contains(x, x+6, 2));
		VERIFY( ranges::contains(x, x+6, 8));
		VERIFY(!ranges::contains(x, x+6, 9));
	}
	{
		test_forward_range<int> r(x);
		VERIFY(!ranges::contains(r, 1));
		VERIFY( ranges::contains(r, 2));
		VERIFY( ranges::contains(r, 8));
		VERIFY(!ranges::contains(r, 9));
	}
	{
		test_input_range<int> r(x);
		VERIFY(!ranges::contains(r, 1));
		VERIFY( ranges::contains(r, 2));
		VERIFY( ranges::contains(r, 8));
		VERIFY(!ranges::contains(r, 9));
	}
	return true;
}

struct X { int i; };

inline HAMON_CXX14_CONSTEXPR bool Test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {3}, {1}, {4} };
	{
		VERIFY(!ranges::contains(x, x+3, 0, &X::i));
		VERIFY( ranges::contains(x, x+3, 1, &X::i));
		VERIFY(!ranges::contains(x, x+3, 2, &X::i));
		VERIFY( ranges::contains(x, x+3, 3, &X::i));
		VERIFY( ranges::contains(x, x+3, 4, &X::i));
	}
	{
		test_forward_range<X> r(x);
		VERIFY(!ranges::contains(r, 0, &X::i));
		VERIFY( ranges::contains(r, 1, &X::i));
		VERIFY(!ranges::contains(r, 2, &X::i));
		VERIFY( ranges::contains(r, 3, &X::i));
		VERIFY( ranges::contains(r, 4, &X::i));
	}
	{
		test_input_range<X> r(x);
		VERIFY(!ranges::contains(r, 0, &X::i));
		VERIFY( ranges::contains(r, 1, &X::i));
		VERIFY(!ranges::contains(r, 2, &X::i));
		VERIFY( ranges::contains(r, 3, &X::i));
		VERIFY( ranges::contains(r, 4, &X::i));
	}
	return true;
}

struct Y { int i; int j; };

inline HAMON_CXX11_CONSTEXPR bool
operator==(Y const& lhs, Y const& rhs)
{
	return lhs.i == rhs.i && lhs.j == rhs.j;
}
inline HAMON_CXX11_CONSTEXPR bool
operator!=(Y const& lhs, Y const& rhs)
{
	return !(lhs == rhs);
}

inline HAMON_CXX14_CONSTEXPR bool Test03()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };
	VERIFY( ranges::contains(y, 2, &Y::i));
	VERIFY(!ranges::contains(y, 4, &Y::i));
	VERIFY(!ranges::contains(y, 5, &Y::i));
	VERIFY( ranges::contains(y, 2, &Y::j));
	VERIFY( ranges::contains(y, 4, &Y::j));
	VERIFY(!ranges::contains(y, 5, &Y::j));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool Test04()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6} };

	VERIFY( ranges::contains(ranges::begin(y), ranges::end(y), {1,2}));
	VERIFY( ranges::contains(ranges::begin(y), ranges::end(y), {2,4}));
	VERIFY(!ranges::contains(ranges::begin(y), ranges::end(y), {1,4}));

	VERIFY( ranges::contains(y, {1,2}));
	VERIFY( ranges::contains(y, {2,4}));
	VERIFY(!ranges::contains(y, {1,4}));

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool TestArray()
{
	namespace ranges = hamon::ranges;

	hamon::array<int, 4> a { 3,1,4,1 };
	VERIFY(!ranges::contains(a, 0));
	VERIFY( ranges::contains(a, 1));
	VERIFY(!ranges::contains(a, 2));
	VERIFY( ranges::contains(a, 3));
	VERIFY( ranges::contains(a, 4));
	VERIFY(!ranges::contains(a, 5));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestVector()
{
	namespace ranges = hamon::ranges;

	hamon::vector<int> v { 1, 3, 5 };
	VERIFY(!ranges::contains(v, 0));
	VERIFY( ranges::contains(v, 1));
	VERIFY(!ranges::contains(v, 2));
	VERIFY( ranges::contains(v, 3));
	VERIFY(!ranges::contains(v, 4));
	VERIFY( ranges::contains(v, 5));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestList()
{
	namespace ranges = hamon::ranges;

	hamon::list<int> v { 1, 2, 3, 5 };
	VERIFY(!ranges::contains(v, 0));
	VERIFY( ranges::contains(v, 1));
	VERIFY( ranges::contains(v, 2));
	VERIFY( ranges::contains(v, 3));
	VERIFY(!ranges::contains(v, 4));
	VERIFY( ranges::contains(v, 5));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestForwardList()
{
	namespace ranges = hamon::ranges;

	hamon::forward_list<int> v { 1, 2, 3, 4 };
	VERIFY(!ranges::contains(v, 0));
	VERIFY( ranges::contains(v, 1));
	VERIFY( ranges::contains(v, 2));
	VERIFY( ranges::contains(v, 3));
	VERIFY( ranges::contains(v, 4));
	VERIFY(!ranges::contains(v, 5));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestMap()
{
	namespace ranges = hamon::ranges;

	hamon::map<int, char> m = { {1,'a'}, {2,'b'} };
	using Pair = hamon::remove_cvref_t<decltype(*m.begin())>;
	VERIFY(!ranges::contains(m, Pair(0, 'a')));
	VERIFY( ranges::contains(m, Pair(1, 'a')));
	VERIFY(!ranges::contains(m, Pair(2, 'a')));
	VERIFY(!ranges::contains(m, Pair(3, 'a')));
	VERIFY(!ranges::contains(m, Pair(0, 'b')));
	VERIFY(!ranges::contains(m, Pair(1, 'b')));
	VERIFY( ranges::contains(m, Pair(2, 'b')));
	VERIFY(!ranges::contains(m, Pair(3, 'b')));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestSet()
{
	namespace ranges = hamon::ranges;

	hamon::set<int> s = { 6, 4, 2 };
	VERIFY(!ranges::contains(s, 0));
	VERIFY(!ranges::contains(s, 1));
	VERIFY( ranges::contains(s, 2));
	VERIFY(!ranges::contains(s, 3));
	VERIFY( ranges::contains(s, 4));
	VERIFY(!ranges::contains(s, 5));
	VERIFY( ranges::contains(s, 6));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestUnorderedMap()
{
	namespace ranges = hamon::ranges;

	hamon::unordered_map<int, char> m = { {1,'a'}, {2,'b'} };
	using Pair = hamon::remove_cvref_t<decltype(*m.begin())>;
	VERIFY(!ranges::contains(m, Pair(0, 'a')));
	VERIFY( ranges::contains(m, Pair(1, 'a')));
	VERIFY(!ranges::contains(m, Pair(2, 'a')));
	VERIFY(!ranges::contains(m, Pair(3, 'a')));
	VERIFY(!ranges::contains(m, Pair(0, 'b')));
	VERIFY(!ranges::contains(m, Pair(1, 'b')));
	VERIFY( ranges::contains(m, Pair(2, 'b')));
	VERIFY(!ranges::contains(m, Pair(3, 'b')));

	return true;
}

inline HAMON_CXX20_CONSTEXPR bool TestUnorderedSet()
{
	namespace ranges = hamon::ranges;

	hamon::unordered_set<int> s = { 6, 4, 2 };
	VERIFY(!ranges::contains(s, 0));
	VERIFY(!ranges::contains(s, 1));
	VERIFY( ranges::contains(s, 2));
	VERIFY(!ranges::contains(s, 3));
	VERIFY( ranges::contains(s, 4));
	VERIFY(!ranges::contains(s, 5));
	VERIFY( ranges::contains(s, 6));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesContainsTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(Test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(TestArray());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestVector());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestList());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestForwardList());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestMap());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestSet());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestUnorderedMap());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(TestUnorderedSet());
}

}	// namespace ranges_contains_test

}	// namespace hamon_algorithm_test
