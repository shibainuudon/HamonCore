/**
 *	@file	unit_test_multiset_equal_range_heterogeneous.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	template<class K>
 *	pair<iterator, iterator>             equal_range(const K& x);
 *	template<class K>
 *	pair<const_iterator, const_iterator> equal_range(const K& x) const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace equal_range_heterogeneous_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S
{
	int value;

	constexpr explicit S(int v) : value(v) {}

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}
};

// template<class K> pair<iterator, iterator> equal_range(const K& x);
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using Iterator = typename Set::iterator;
	using Result = hamon::pair<Iterator, Iterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<int const&>())), "");

	Set v;

	VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(S{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 1), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});

	v.emplace(S{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(S{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 4), v.end()});

	v.emplace(S{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 5), v.end()});

	return true;
}

// template<class K> pair<const_iterator, const_iterator> equal_range(const K& x) const;
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;
	using Result = hamon::pair<ConstIterator, ConstIterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{1}, S{4}, S{5}, S{5}, S{5}};

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(3) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(4) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(5) == Result{hamon::next(v.begin(), 4), v.end()});
	VERIFY(v.equal_range(6) == Result{v.end(), v.end()});

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, EqualRangeHeterogeneousTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
}

}	// namespace equal_range_heterogeneous_test

}	// namespace hamon_multiset_test
