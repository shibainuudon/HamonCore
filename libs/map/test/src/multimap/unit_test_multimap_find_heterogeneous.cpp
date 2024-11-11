/**
 *	@file	unit_test_multimap_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K> iterator       find(const K& x);
 *	template<class K> const_iterator find(const K& x) const;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_multimap_test
{

namespace find_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct S
{
	int value;

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
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<S, float, hamon::less<>>;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int const&>())), "");

	Map v;

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == v.end());
	VERIFY(v.find(3) == v.end());

	v.emplace(S{2}, 10.0f);

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 0));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1}, 20.0f);

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == hamon::next(v.begin(), 0));
	VERIFY(v.find(2) == hamon::next(v.begin(), 1));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 30.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 1));
	VERIFY(v.find(2) == hamon::next(v.begin(), 2));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 40.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 2));
	VERIFY(v.find(2) == hamon::next(v.begin(), 3));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 50.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 3));
	VERIFY(v.find(2) == hamon::next(v.begin(), 4));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1}, 60.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 3));
	VERIFY(v.find(2) == hamon::next(v.begin(), 5));
	VERIFY(v.find(3) == v.end());

	return true;
}

// template<class K> const_iterator find(const K& x) const;
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<S, float, hamon::less<>>;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{2}, 10.5f},
		{S{5}, 11.5f},
		{S{5}, 11.5f},
		{S{6}, 12.5f},
		{S{8}, 13.5f},
		{S{8}, 13.5f},
		{S{8}, 13.5f},
	};

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 0));
	VERIFY(v.find(3) == v.end());
	VERIFY(v.find(4) == v.end());
	VERIFY(v.find(5) == hamon::next(v.begin(), 1));
	VERIFY(v.find(6) == hamon::next(v.begin(), 3));
	VERIFY(v.find(7) == v.end());
	VERIFY(v.find(8) == hamon::next(v.begin(), 4));
	VERIFY(v.find(9) == v.end());

	return true;
}

#undef VERIFY

struct LightKey
{
	int x;
};

struct FatKey
{
	int x;
	int data[1000]; // a heavy blob
};

// As detailed above, the container must use std::less<> (or other transparent
// Comparator) to access these overloads. This includes standard overloads,
// such as comparison between std::string and std::string_view.
bool operator<(const FatKey& fk, const LightKey& lk) { return fk.x < lk.x; }
bool operator<(const LightKey& lk, const FatKey& fk) { return lk.x < fk.x; }
bool operator<(const FatKey& fk1, const FatKey& fk2) { return fk1.x < fk2.x; }

GTEST_TEST(MultimapTest, FindHeterogeneousTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	// https://en.cppreference.com/w/cpp/container/multimap/find
	{
		// Transparent comparison demo.
		hamon::multimap<FatKey, char, hamon::less<>> example2 {{{1, {}}, 'a'}, {{2, {}}, 'b'}};

		LightKey lk = {2};
		auto search = example2.find(lk);
		EXPECT_TRUE(search != example2.end());
		EXPECT_EQ(2, search->first.x);
		EXPECT_EQ('b', search->second);
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace find_heterogeneous_test

}	// namespace hamon_multimap_test

#endif
