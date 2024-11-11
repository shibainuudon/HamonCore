/**
 *	@file	unit_test_multiset_find.cpp
 *
 *	@brief	find のテスト
 *
 *	iterator       find(const key_type& x);
 *	const_iterator find(const key_type& x) const;
 *	template<class K> iterator       find(const K& x);
 *	template<class K> const_iterator find(const K& x) const;
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

namespace find_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator find(const key_type& x);
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");

	Set v;

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == v.end());
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{1});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{1});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{0});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 3));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 3));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 3));
	VERIFY(v.find(Key{3}) == v.end());

	return true;
}

// const_iterator find(const key_type& x) const;
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<Key>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");

	Set const v {Key{3}, Key{1}, Key{1}, Key{3}, Key{1}, Key{4}};

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == hamon::next(v.begin(), 3));
	VERIFY(v.find(Key{4}) == hamon::next(v.begin(), 5));
	VERIFY(v.find(Key{5}) == v.end());

	return true;
}

#if !defined(HAMON_USE_STD_MULTISET) || \
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

// template<class K> iterator find(const K& x);
MULTISET_TEST_CONSTEXPR bool test3()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<int const&>())), "");

	Set v;

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == v.end());
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == v.end());
	VERIFY(v.find(3) == v.end());

	v.emplace(S{2});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 1));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 2));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 2));
	VERIFY(v.find(2) == hamon::next(v.begin(), 3));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 2));
	VERIFY(v.find(2) == hamon::next(v.begin(), 4));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0});

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 3));
	VERIFY(v.find(2) == hamon::next(v.begin(), 5));
	VERIFY(v.find(3) == v.end());

	return true;
}

// template<class K> const_iterator find(const K& x) const;
MULTISET_TEST_CONSTEXPR bool test4()
{
	using Set = hamon::multiset<S, hamon::less<>>;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<int const&>())), "");

	Set const v {S{0}, S{1}, S{1}, S{4}, S{5}, S{5}, S{5}};

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 1));
	VERIFY(v.find(2) == v.end());
	VERIFY(v.find(3) == v.end());
	VERIFY(v.find(4) == hamon::next(v.begin(), 3));
	VERIFY(v.find(5) == hamon::next(v.begin(), 4));
	VERIFY(v.find(6) == v.end());

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MultisetTest, FindTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

#if !defined(HAMON_USE_STD_MULTISET) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test3());
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_multiset_test
