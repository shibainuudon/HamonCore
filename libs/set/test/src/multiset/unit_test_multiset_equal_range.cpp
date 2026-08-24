/**
 *	@file	unit_test_multiset_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	pair<iterator, iterator>               equal_range(const key_type& x);
 *	pair<const_iterator, const_iterator>   equal_range(const key_type& x) const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_multiset_test
{

namespace equal_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// pair<iterator, iterator> equal_range(const key_type& x);
template <typename Key>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;
	using Result = hamon::pair<Iterator, Iterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<Key const&>())), "");

	Set v;

	VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{1});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});

	v.emplace(Key{0});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	v.emplace(Key{2});

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), v.end()});

	return true;
}

// pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
template <typename Key>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<Key>;
	using ConstIterator = typename Set::const_iterator;
	using Result = hamon::pair<ConstIterator, ConstIterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<Key const&>())), "");

	Set const v {Key{1}, Key{1}, Key{1}, Key{3}, Key{3}, Key{4}};

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(3) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(4) == Result{hamon::next(v.begin(), 5), v.end()});
	VERIFY(v.equal_range(5) == Result{v.end(), v.end()});

	return true;
}

#undef VERIFY

template <typename I>
std::string ToString(I first, I lb, I ub, I last)
{
	std::stringstream out;
	for (I i {first}; i != lb; ++i)
	{
		out << *i << ' ';
	}
	out << "[ ";

	for (I i {lb}; i != ub; ++i)
	{
		out << *i << ' ';
	}
	out << ") ";

	for (I i {ub}; i != last; ++i)
	{
		out << *i << ' ';
	}

	return out.str();
}

template <typename T, typename C>
std::string ToStringEqualRange(const hamon::multiset<T, C>& c, T key)
{
	auto r = c.equal_range(key);
	return ToString(hamon::begin(c), r.first, r.second, hamon::end(c));
}

GTEST_TEST(MultisetTest, EqualRangeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	// https://en.cppreference.com/w/cpp/container/multiset/equal_range
	{
		hamon::multiset<int> c{4, 3, 2, 1, 3, 3};
		EXPECT_EQ("[ 1 2 3 3 3 4 ) ", ToString(hamon::begin(c), hamon::begin(c), hamon::end(c), hamon::end(c)));
		EXPECT_EQ("[ ) 1 2 3 3 3 4 ", ToStringEqualRange(c, 0));
		EXPECT_EQ("[ 1 ) 2 3 3 3 4 ", ToStringEqualRange(c, 1));
		EXPECT_EQ("1 [ 2 ) 3 3 3 4 ", ToStringEqualRange(c, 2));
		EXPECT_EQ("1 2 [ 3 3 3 ) 4 ", ToStringEqualRange(c, 3));
		EXPECT_EQ("1 2 3 3 3 [ 4 ) ", ToStringEqualRange(c, 4));
		EXPECT_EQ("1 2 3 3 3 4 [ ) ", ToStringEqualRange(c, 5));
	}
}

}	// namespace equal_range_test

}	// namespace hamon_multiset_test
