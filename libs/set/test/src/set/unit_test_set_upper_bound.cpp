﻿/**
 *	@file	unit_test_set_upper_bound.cpp
 *
 *	@brief	upper_bound のテスト
 *
 *	iterator       upper_bound(const key_type& x);
 *	const_iterator upper_bound(const key_type& x) const;
 *	template<class K> iterator       upper_bound(const K& x);
 *	template<class K> const_iterator upper_bound(const K& x) const;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace upper_bound_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator upper_bound(const key_type& x);
template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;
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

	v.emplace(Key{2});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	v.emplace(Key{0});

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(Key{2}) == v.end());
	VERIFY(v.upper_bound(Key{3}) == v.end());

	return true;
}

// const_iterator upper_bound(const key_type& x) const;
template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::set<Key>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().upper_bound(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().upper_bound(hamon::declval<Key const&>())), "");

	Set const v {Key{4}, Key{3}, Key{1}, Key{1}, Key{1}, Key{3}};

	VERIFY(v.upper_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.upper_bound(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{2}) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(Key{3}) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(Key{4}) == v.end());
	VERIFY(v.upper_bound(Key{5}) == v.end());

	return true;
}

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

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

// template<class K> iterator upper_bound(const K& x);
SET_TEST_CONSTEXPR bool test3()
{
	using Set = hamon::set<S, hamon::less<>>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().upper_bound(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().upper_bound(hamon::declval<int const&>())), "");

	Set v;

	VERIFY(v.upper_bound(0) == v.end());
	VERIFY(v.upper_bound(1) == v.end());
	VERIFY(v.upper_bound(2) == v.end());
	VERIFY(v.upper_bound(3) == v.end());

	v.emplace(S{0});

	VERIFY(v.upper_bound(0) == v.end());
	VERIFY(v.upper_bound(1) == v.end());
	VERIFY(v.upper_bound(2) == v.end());
	VERIFY(v.upper_bound(3) == v.end());

	v.emplace(S{2});

	VERIFY(v.upper_bound(0) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(1) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(2) == v.end());
	VERIFY(v.upper_bound(3) == v.end());

	v.emplace(S{1});

	VERIFY(v.upper_bound(0) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(1) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(2) == v.end());
	VERIFY(v.upper_bound(3) == v.end());

	return true;
}

// template<class K> const_iterator upper_bound(const K& x) const;
SET_TEST_CONSTEXPR bool test4()
{
	using Set = hamon::set<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().upper_bound(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().upper_bound(hamon::declval<int const&>())), "");

	Set const v {S{5}, S{5}, S{5}, S{4}, S{1}, S{1}, S{0}};

	VERIFY(v.upper_bound(0) == hamon::next(v.begin(), 1));
	VERIFY(v.upper_bound(1) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(2) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(3) == hamon::next(v.begin(), 2));
	VERIFY(v.upper_bound(4) == hamon::next(v.begin(), 3));
	VERIFY(v.upper_bound(5) == v.end());
	VERIFY(v.upper_bound(6) == v.end());

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(SetTest, UpperBoundTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

#if !defined(HAMON_USE_STD_SET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test3());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace upper_bound_test

}	// namespace hamon_set_test