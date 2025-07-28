/**
 *	@file	unit_test_flat_multiset_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	constexpr friend bool operator==(const flat_multiset& x, const flat_multiset& y);
 *
 *	constexpr friend synth-three-way-result<value_type>
 *	operator<=>(const flat_multiset& x, const flat_multiset& y);
 */

#include <hamon/flat_set/flat_multiset.hpp>
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
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() == hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() != hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() <  hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() >  hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() <= hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() >= hamon::declval<Set const&>()), bool>::value, "");

	static_assert(!noexcept(hamon::declval<Set const&>() == hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() != hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() <  hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() >  hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() <= hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() >= hamon::declval<Set const&>()), "");

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	static_assert(!hamon::is_same<decltype(hamon::declval<Set const&>() <=> hamon::declval<Set const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>() <=> hamon::declval<Set const&>()), "");
#endif

	{
		Set const v1
		{
			Key{1},
			Key{2},
			Key{3},
		};

		Set const v2
		{
			Key{1},
			Key{3},
			Key{2},
		};

		Set const v3
		{
			Key{1},
			Key{1},
			Key{3},
		};

		Set const v4
		{
			Key{1},
			Key{2},
			Key{4},
		};

		Set const v5
		{
			Key{1},
			Key{2},
		};

		Set const v6
		{
			Key{1},
			Key{2},
			Key{3},
			Key{3},
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
		Set const v1;
		Set const v2;

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

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, OpCompareTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::greater<double>>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, hamon::less<int>>()));
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_flat_multiset_test
