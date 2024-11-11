/**
 *	@file	unit_test_multimap_count.cpp
 *
 *	@brief	count のテスト
 *
 *	size_type      count(const key_type& x) const;
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace count_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// size_type count(const key_type& x) const;
template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{3}, T{50}},
		{Key{3}, T{30}},
		{Key{7}, T{70}},
		{Key{5}, T{60}},
		{Key{2}, T{20}},
		{Key{2}, T{10}},
		{Key{3}, T{40}},
	};

	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 2);
	VERIFY(v.count(Key{3}) == 3);
	VERIFY(v.count(Key{4}) == 0);
	VERIFY(v.count(Key{5}) == 1);
	VERIFY(v.count(Key{6}) == 0);
	VERIFY(v.count(Key{7}) == 1);
	VERIFY(v.count(Key{8}) == 0);

	return true;
}

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

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

// template<class K> size_type count(const K& x) const;
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<S, float, hamon::less<>>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{5}, 11.5f},
		{S{2}, 10.5f},
		{S{8}, 13.5f},
		{S{8}, 13.5f},
		{S{5}, 11.5f},
		{S{8}, 13.5f},
		{S{6}, 12.5f},
	};

	VERIFY(v.count(0) == 0);
	VERIFY(v.count(1) == 0);
	VERIFY(v.count(2) == 1);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 0);
	VERIFY(v.count(5) == 2);
	VERIFY(v.count(6) == 1);
	VERIFY(v.count(7) == 0);
	VERIFY(v.count(8) == 3);
	VERIFY(v.count(9) == 0);

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MultimapTest, CountTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
#endif
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace count_test

}	// namespace hamon_multimap_test
