/**
 *	@file	unit_test_multimap_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Compare, class Allocator>
 *	bool operator==(const multimap<Key, T, Compare, Allocator>& x,
 *		const multimap<Key, T, Compare, Allocator>& y);
 *
 *	template<class Key, class T, class Compare, class Allocator>
 *	synth-three-way-result<pair<const Key, T>>
 *	operator<=>(const multimap<Key, T, Compare, Allocator>& x,
 *		const multimap<Key, T, Compare, Allocator>& y);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::multimap<Key, T>;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v == v), bool>::value, "");
		static_assert(hamon::is_same<decltype(v != v), bool>::value, "");
		static_assert(hamon::is_same<decltype(v <  v), bool>::value, "");
		static_assert(hamon::is_same<decltype(v >  v), bool>::value, "");
		static_assert(hamon::is_same<decltype(v <= v), bool>::value, "");
		static_assert(hamon::is_same<decltype(v >= v), bool>::value, "");
		static_assert(!noexcept(v == v), "");
		static_assert(!noexcept(v != v), "");
		static_assert(!noexcept(v <  v), "");
		static_assert(!noexcept(v >  v), "");
		static_assert(!noexcept(v <= v), "");
		static_assert(!noexcept(v >= v), "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		static_assert(!hamon::is_same<decltype(v <=> v), bool>::value, "");
		static_assert(!noexcept(v <=> v), "");
#endif
	}
	{
		Map const v1
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
		};

		Map const v2
		{
			{Key{1}, T{10}},
			{Key{3}, T{30}},
			{Key{2}, T{20}},
		};

		Map const v3
		{
			{Key{1}, T{10}},
			{Key{2}, T{10}},
			{Key{3}, T{30}},
		};

		Map const v4
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{4}, T{30}},
		};

		Map const v5
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
		};

		Map const v6
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{4}, T{40}},
		};

		Map const v7
		{
			{Key{1}, T{10}},
			{Key{1}, T{40}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
		};

		VERIFY( (v1 == v1));
		VERIFY( (v1 == v2));
		VERIFY(!(v1 == v3));
		VERIFY(!(v1 == v4));
		VERIFY(!(v1 == v5));
		VERIFY(!(v1 == v6));
		VERIFY(!(v1 == v7));

		VERIFY(!(v1 != v1));
		VERIFY(!(v1 != v2));
		VERIFY( (v1 != v3));
		VERIFY( (v1 != v4));
		VERIFY( (v1 != v5));
		VERIFY( (v1 != v6));
		VERIFY( (v1 != v7));

		VERIFY(!(v1 < v1));
		VERIFY(!(v1 < v2));
		VERIFY(!(v1 < v3));
		VERIFY( (v1 < v4));
		VERIFY(!(v1 < v5));
		VERIFY( (v1 < v6));
		VERIFY(!(v1 < v7));

		VERIFY(!(v1 > v1));
		VERIFY(!(v1 > v2));
		VERIFY( (v1 > v3));
		VERIFY(!(v1 > v4));
		VERIFY( (v1 > v5));
		VERIFY(!(v1 > v6));
		VERIFY( (v1 > v7));

		VERIFY( (v1 <= v1));
		VERIFY( (v1 <= v2));
		VERIFY(!(v1 <= v3));
		VERIFY( (v1 <= v4));
		VERIFY(!(v1 <= v5));
		VERIFY( (v1 <= v6));
		VERIFY(!(v1 <= v7));

		VERIFY( (v1 >= v1));
		VERIFY( (v1 >= v2));
		VERIFY( (v1 >= v3));
		VERIFY(!(v1 >= v4));
		VERIFY( (v1 >= v5));
		VERIFY(!(v1 >= v6));
		VERIFY( (v1 >= v7));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(v1 <=> v1));
		VERIFY( hamon::is_eq(v1 <=> v2));
		VERIFY(!hamon::is_eq(v1 <=> v3));
		VERIFY(!hamon::is_eq(v1 <=> v4));
		VERIFY(!hamon::is_eq(v1 <=> v5));
		VERIFY(!hamon::is_eq(v1 <=> v6));
		VERIFY(!hamon::is_eq(v1 <=> v7));

		VERIFY(!hamon::is_lt(v1 <=> v1));
		VERIFY(!hamon::is_lt(v1 <=> v2));
		VERIFY(!hamon::is_lt(v1 <=> v3));
		VERIFY( hamon::is_lt(v1 <=> v4));
		VERIFY(!hamon::is_lt(v1 <=> v5));
		VERIFY( hamon::is_lt(v1 <=> v6));
		VERIFY(!hamon::is_lt(v1 <=> v7));

		VERIFY(!hamon::is_gt(v1 <=> v1));
		VERIFY(!hamon::is_gt(v1 <=> v2));
		VERIFY( hamon::is_gt(v1 <=> v3));
		VERIFY(!hamon::is_gt(v1 <=> v4));
		VERIFY( hamon::is_gt(v1 <=> v5));
		VERIFY(!hamon::is_gt(v1 <=> v6));
		VERIFY( hamon::is_gt(v1 <=> v7));
#endif
	}

	{
		Map const v1;
		Map const v2;

		VERIFY( (v1 == v1));
		VERIFY( (v1 == v2));

		VERIFY(!(v1 != v1));
		VERIFY(!(v1 != v2));

		VERIFY(!(v1 < v1));
		VERIFY(!(v1 < v2));

		VERIFY(!(v1 > v1));
		VERIFY(!(v1 > v2));

		VERIFY( (v1 <= v1));
		VERIFY( (v1 <= v2));

		VERIFY( (v1 >= v1));
		VERIFY( (v1 >= v2));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(v1 <=> v1));
		VERIFY( hamon::is_eq(v1 <=> v2));

		VERIFY(!hamon::is_lt(v1 <=> v1));
		VERIFY(!hamon::is_lt(v1 <=> v2));

		VERIFY(!hamon::is_gt(v1 <=> v1));
		VERIFY(!hamon::is_gt(v1 <=> v2));
#endif
	}
	{
		Map const v1 {{Key{1}, T{1}}};
		Map const v2 {{Key{1}, T{0}}};
		Map const v3 {{Key{1}, T{2}}};
		Map const v4 {{Key{0}, T{1}}};
		Map const v5 {{Key{2}, T{1}}};

		VERIFY( (v1 == v1));
		VERIFY(!(v1 == v2));
		VERIFY(!(v1 == v3));
		VERIFY(!(v1 == v4));
		VERIFY(!(v1 == v5));

		VERIFY(!(v1 != v1));
		VERIFY( (v1 != v2));
		VERIFY( (v1 != v3));
		VERIFY( (v1 != v4));
		VERIFY( (v1 != v5));

		VERIFY(!(v1 < v1));
		VERIFY(!(v1 < v2));
		VERIFY( (v1 < v3));
		VERIFY(!(v1 < v4));
		VERIFY( (v1 < v5));

		VERIFY(!(v1 > v1));
		VERIFY( (v1 > v2));
		VERIFY(!(v1 > v3));
		VERIFY( (v1 > v4));
		VERIFY(!(v1 > v5));

		VERIFY( (v1 <= v1));
		VERIFY(!(v1 <= v2));
		VERIFY( (v1 <= v3));
		VERIFY(!(v1 <= v4));
		VERIFY( (v1 <= v5));

		VERIFY( (v1 >= v1));
		VERIFY( (v1 >= v2));
		VERIFY(!(v1 >= v3));
		VERIFY( (v1 >= v4));
		VERIFY(!(v1 >= v5));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(v1 <=> v1));
		VERIFY(!hamon::is_eq(v1 <=> v2));
		VERIFY(!hamon::is_eq(v1 <=> v3));
		VERIFY(!hamon::is_eq(v1 <=> v4));
		VERIFY(!hamon::is_eq(v1 <=> v5));

		VERIFY(!hamon::is_lt(v1 <=> v1));
		VERIFY(!hamon::is_lt(v1 <=> v2));
		VERIFY( hamon::is_lt(v1 <=> v3));
		VERIFY(!hamon::is_lt(v1 <=> v4));
		VERIFY( hamon::is_lt(v1 <=> v5));

		VERIFY(!hamon::is_gt(v1 <=> v1));
		VERIFY( hamon::is_gt(v1 <=> v2));
		VERIFY(!hamon::is_gt(v1 <=> v3));
		VERIFY( hamon::is_gt(v1 <=> v4));
		VERIFY(!hamon::is_gt(v1 <=> v5));
#endif
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, OpCompareTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_multimap_test
