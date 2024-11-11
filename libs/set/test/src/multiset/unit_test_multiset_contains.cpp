/**
 *	@file	unit_test_multiset_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	bool           contains(const key_type& x) const;
 *	template<class K> bool contains(const K& x) const;
 */

#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_MULTISET) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_multiset_test
{

namespace contains_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// bool contains(const key_type& x) const;
template <typename Key>
MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<Key const&>())), "");

	Set const v {Key{1}, Key{1}, Key{1}, Key{3}, Key{3}, Key{4}};

	VERIFY(v.contains(Key{0}) == false);
	VERIFY(v.contains(Key{1}) == true);
	VERIFY(v.contains(Key{2}) == false);
	VERIFY(v.contains(Key{3}) == true);
	VERIFY(v.contains(Key{4}) == true);
	VERIFY(v.contains(Key{5}) == false);

	return true;
}

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

// template<class K> bool contains(const K& x) const;
MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::multiset<S, hamon::less<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().contains(hamon::declval<int const&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>().contains(hamon::declval<int const&>())), "");

	Set const v {S{5}, S{1}, S{1}, S{4}, S{0}, S{5}, S{5}};

	VERIFY(v.contains(0) == true);
	VERIFY(v.contains(1) == true);
	VERIFY(v.contains(2) == false);
	VERIFY(v.contains(3) == false);
	VERIFY(v.contains(4) == true);
	VERIFY(v.contains(5) == true);
	VERIFY(v.contains(6) == false);

	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, ContainsTest)
{
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	// https://en.cppreference.com/w/cpp/container/multiset/contains
	{
		hamon::multiset<int> example{1, 2, 3, 4};
		EXPECT_TRUE(example.contains(2));
		EXPECT_FALSE(example.contains(5));
	}
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace contains_test

}	// namespace hamon_multiset_test

#endif
