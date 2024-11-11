/**
 *	@file	unit_test_set_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class Compare, class Allocator>
 *	bool operator==(const set<Key, Compare, Allocator>& x,
 *		const set<Key, Compare, Allocator>& y);
 *
 *	template<class Key, class Compare, class Allocator>
 *	synth-three-way-result<Key> operator<=>(const set<Key, Compare, Allocator>& x,
 *		const set<Key, Compare, Allocator>& y);
 */

#include <hamon/set/set.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::set<Key>;

	{
		Set v;
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
		Set const v1 {1, 2, 3};
		Set const v2 {3, 1, 2};
		Set const v3 {0, 2, 3};
		Set const v4 {1, 2, 4};
		Set const v5 {1, 2};
		Set const v6 {1, 2, 3, 4};
		Set const v7 {1, 1, 2, 3};

		VERIFY( (v1 == v1));
		VERIFY( (v1 == v2));
		VERIFY(!(v1 == v3));
		VERIFY(!(v1 == v4));
		VERIFY(!(v1 == v5));
		VERIFY(!(v1 == v6));
		VERIFY( (v1 == v7));

		VERIFY(!(v1 != v1));
		VERIFY(!(v1 != v2));
		VERIFY( (v1 != v3));
		VERIFY( (v1 != v4));
		VERIFY( (v1 != v5));
		VERIFY( (v1 != v6));
		VERIFY(!(v1 != v7));

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
		VERIFY(!(v1 > v7));

		VERIFY( (v1 <= v1));
		VERIFY( (v1 <= v2));
		VERIFY(!(v1 <= v3));
		VERIFY( (v1 <= v4));
		VERIFY(!(v1 <= v5));
		VERIFY( (v1 <= v6));
		VERIFY( (v1 <= v7));

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
		VERIFY( hamon::is_eq(v1 <=> v7));

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
		VERIFY(!hamon::is_gt(v1 <=> v7));
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

GTEST_TEST(SetTest, OpCompareTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_set_test
