/**
 *	@file	unit_test_multiset_upper_bound.cpp
 *
 *	@brief	upper_bound のテスト
 *
 *	iterator       upper_bound(const key_type& x);
 *	const_iterator upper_bound(const key_type& x) const;
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

namespace upper_bound_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator upper_bound(const key_type& x);
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().upper_bound(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().upper_bound(hamon::declval<Key const&>())), "");

	Set v;

	VERIFY(v.upper_bound(Key{0}) == v.end());
	VERIFY(v.upper_bound(Key{1}) == v.end());
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{1});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == v.end());
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{1});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == v.end());
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{0});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	return true;
}

// const_iterator upper_bound(const key_type& x) const;
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<Key>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().upper_bound(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().upper_bound(hamon::declval<Key const&>())), "");

	Set const v {Key{4}, Key{3}, Key{1}, Key{1}, Key{1}, Key{3}};

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(Key{2}) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(Key{3}) == hamon::next(v.begin(), 5));
	VERIFY(v.upper_bound(Key{4}) == v.end());
	VERIFY(v.upper_bound(Key{5}) == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, UpperBoundTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace upper_bound_test

}	// namespace hamon_multiset_test
