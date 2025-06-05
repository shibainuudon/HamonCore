/**
 *	@file	unit_test_flat_multimap_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	constexpr friend bool operator==(const flat_multimap& x, const flat_multimap& y);
 *
 *	constexpr friend synth-three-way-result<value_type>
 *	operator<=>(const flat_multimap& x, const flat_multimap& y);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/compare.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() == hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() != hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() <  hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() >  hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() <= hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() >= hamon::declval<Map const&>()), bool>::value, "");

	static_assert(!noexcept(hamon::declval<Map const&>() == hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() != hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() <  hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() >  hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() <= hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() >= hamon::declval<Map const&>()), "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!hamon::is_same<decltype(hamon::declval<Map const&>() <=> hamon::declval<Map const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>() <=> hamon::declval<Map const&>()), "");
#endif

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

		VERIFY( (v1 == v1));
		VERIFY( (v1 == v2));
		VERIFY(!(v1 == v3));
		VERIFY(!(v1 == v4));
		VERIFY(!(v1 == v5));
		VERIFY(!(v1 == v6));

		VERIFY(!(v1 != v1));
		VERIFY(!(v1 != v2));
		VERIFY( (v1 != v3));
		VERIFY( (v1 != v4));
		VERIFY( (v1 != v5));
		VERIFY( (v1 != v6));

		VERIFY(!(v1 < v1));
		VERIFY(!(v1 < v2));
		VERIFY(!(v1 < v3));
		VERIFY( (v1 < v4));
		VERIFY(!(v1 < v5));
		VERIFY( (v1 < v6));

		VERIFY(!(v1 > v1));
		VERIFY(!(v1 > v2));
		VERIFY( (v1 > v3));
		VERIFY(!(v1 > v4));
		VERIFY( (v1 > v5));
		VERIFY(!(v1 > v6));

		VERIFY( (v1 <= v1));
		VERIFY( (v1 <= v2));
		VERIFY(!(v1 <= v3));
		VERIFY( (v1 <= v4));
		VERIFY(!(v1 <= v5));
		VERIFY( (v1 <= v6));

		VERIFY( (v1 >= v1));
		VERIFY( (v1 >= v2));
		VERIFY( (v1 >= v3));
		VERIFY(!(v1 >= v4));
		VERIFY( (v1 >= v5));
		VERIFY(!(v1 >= v6));

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		VERIFY( hamon::is_eq(v1 <=> v1));
		VERIFY( hamon::is_eq(v1 <=> v2));
		VERIFY(!hamon::is_eq(v1 <=> v3));
		VERIFY(!hamon::is_eq(v1 <=> v4));
		VERIFY(!hamon::is_eq(v1 <=> v5));
		VERIFY(!hamon::is_eq(v1 <=> v6));

		VERIFY(!hamon::is_lt(v1 <=> v1));
		VERIFY(!hamon::is_lt(v1 <=> v2));
		VERIFY(!hamon::is_lt(v1 <=> v3));
		VERIFY( hamon::is_lt(v1 <=> v4));
		VERIFY(!hamon::is_lt(v1 <=> v5));
		VERIFY( hamon::is_lt(v1 <=> v6));

		VERIFY(!hamon::is_gt(v1 <=> v1));
		VERIFY(!hamon::is_gt(v1 <=> v2));
		VERIFY( hamon::is_gt(v1 <=> v3));
		VERIFY(!hamon::is_gt(v1 <=> v4));
		VERIFY( hamon::is_gt(v1 <=> v5));
		VERIFY(!hamon::is_gt(v1 <=> v6));
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

GTEST_TEST(FlatMultimapTest, OpCompareTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_flat_multimap_test
