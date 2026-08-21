/**
 *	@file	unit_test_forward_list_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class T, class Allocator>
 *	bool operator==(const forward_list<T, Allocator>& x, const forward_list<T, Allocator>& y);
 *
 *	template<class T, class Allocator>
 *	synth-three-way-result<T>
 *	operator<=>(const forward_list<T, Allocator>& x, const forward_list<T, Allocator>& y);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
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
		ForwardList const v1 {1, 2, 3};
		ForwardList const v2 {1, 2, 3};
		ForwardList const v3 {0, 2, 3};
		ForwardList const v4 {1, 2, 4};
		ForwardList const v5 {1, 2};
		ForwardList const v6 {1, 2, 3, 4};

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
		ForwardList const v1;
		ForwardList const v2;

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

GTEST_TEST(ForwardListTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_compare_test

}	// namespace hamon_forward_list_test
