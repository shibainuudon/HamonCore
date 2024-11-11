/**
 *	@file	unit_test_map_lower_bound_heterogeneous.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	template<class K> iterator       lower_bound(const K& x);
 *	template<class K> const_iterator lower_bound(const K& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

namespace hamon_map_test
{

namespace lower_bound_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
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

// template<class K> iterator lower_bound(const K& x);
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().lower_bound(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().lower_bound(hamon::declval<int const&>())), "");

	Map v;

	VERIFY(v.lower_bound(0) == v.end());
	VERIFY(v.lower_bound(1) == v.end());
	VERIFY(v.lower_bound(2) == v.end());
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{2}, 10.0f);

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{1}, 20.0f);

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(3) == v.end());

	v.emplace(S{0}, 20.0f);

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(3) == v.end());

	return true;
}

// template<class K> const_iterator lower_bound(const K& x) const;
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().lower_bound(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().lower_bound(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{8}, 13.5f},
		{S{2}, 10.5f},
		{S{5}, 11.5f},
		{S{8}, 13.5f},
		{S{6}, 12.5f},
		{S{8}, 13.5f},
		{S{5}, 11.5f},
	};

	VERIFY(v.lower_bound(0) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(1) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(2) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(3) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(4) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(5) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(6) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(7) == hamon::next(v.begin(), 3));
	VERIFY(v.lower_bound(8) == hamon::next(v.begin(), 3));
	VERIFY(v.lower_bound(9) == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, LowerBoundHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace lower_bound_heterogeneous_test

}	// namespace hamon_map_test

#endif
