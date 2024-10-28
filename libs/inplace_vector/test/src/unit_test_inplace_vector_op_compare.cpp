/**
 *	@file	unit_test_inplace_vector_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	constexpr friend bool
 *	operator==(const inplace_vector& x,const inplace_vector& y);
 *
 *	constexpr friend synth-three-way-result<T>
 *	operator<=>(const inplace_vector& x, const inplace_vector& y);
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/compare.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_inplace_vector_test
{

namespace op_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_0()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector v;
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
		InplaceVector const v1;
		InplaceVector const v2;

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

template <typename T, hamon::size_t N>
HAMON_CXX14_CONSTEXPR bool test_impl_4()
{
	using InplaceVector = hamon::inplace_vector<T, N>;

	{
		InplaceVector const v1 {1, 2, 3};
		InplaceVector const v2 {1, 2, 3};
		InplaceVector const v3 {0, 2, 3};
		InplaceVector const v4 {1, 2, 4};
		InplaceVector const v5 {1, 2};
		InplaceVector const v6 {1, 2, 3, 4};

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

	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	VERIFY((test_impl_0<T, 0>()));
	VERIFY((test_impl_0<T, 1>()));
	VERIFY((test_impl_0<T, 4>()));
	VERIFY((test_impl_0<T, 5>()));
	VERIFY((test_impl_0<T, 10>()));

//	VERIFY((test_impl_4<T, 0>()));
//	VERIFY((test_impl_4<T, 1>()));
	VERIFY((test_impl_4<T, 4>()));
	VERIFY((test_impl_4<T, 5>()));
	VERIFY((test_impl_4<T, 10>()));

	return true;
}

#undef VERIFY

GTEST_TEST(InplaceVectorTest, OpCompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/inplace_vector/operator_cmp
	{
		hamon::inplace_vector<int, 4> a {1, 2, 3}, b {1, 2, 3}, c {7, 8, 9, 10};

		// Compare equal containers
		EXPECT_TRUE((a != b) == false);
		EXPECT_TRUE((a == b) == true);
		EXPECT_TRUE((a <  b) == false);
		EXPECT_TRUE((a <= b) == true);
		EXPECT_TRUE((a >  b) == false);
		EXPECT_TRUE((a >= b) == true);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE((a <=> b) >= 0);
		EXPECT_TRUE((a <=> b) <= 0);
		EXPECT_TRUE((a <=> b) == 0);
#endif

		// Compare non equal containers
		EXPECT_TRUE((a != c) == true);
		EXPECT_TRUE((a == c) == false);
		EXPECT_TRUE((a <  c) == true);
		EXPECT_TRUE((a <= c) == true);
		EXPECT_TRUE((a >  c) == false);
		EXPECT_TRUE((a >= c) == false);
#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		EXPECT_TRUE((a <=> c) <  0);
		EXPECT_TRUE((a <=> c) != 0);
		EXPECT_TRUE((a <=> c) <= 0);
#endif
	}
}

}	// namespace op_compare_test

}	// namespace hamon_inplace_vector_test
