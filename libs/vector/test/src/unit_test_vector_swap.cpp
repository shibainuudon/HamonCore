/**
 *	@file	unit_test_vector_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *  constexpr void swap(vector&)
 *    noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value ||
 *             allocator_traits<Allocator>::is_always_equal::value);
 *
 *  template<class T, class Allocator>
 *  constexpr void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
 *    noexcept(noexcept(x.swap(y)));
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test()
{
	using T = int;
	using Vector = hamon::vector<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Vector&>().swap(hamon::declval<Vector&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(swap(hamon::declval<Vector&>(), hamon::declval<Vector&>())),
		void
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Vector&>().swap(hamon::declval<Vector&>())), "");
	static_assert(noexcept(
		swap(hamon::declval<Vector&>(), hamon::declval<Vector&>())), "");

	{
		Vector v1 {1,2,3};
		Vector v2 {11,12,13,14};
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 11);
		VERIFY(v2[1] == 12);
		VERIFY(v2[2] == 13);
		VERIFY(v2[3] == 14);

		v1.swap(v2);
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 11);
		VERIFY(v1[1] == 12);
		VERIFY(v1[2] == 13);
		VERIFY(v1[3] == 14);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);

		swap(v1, v2);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 11);
		VERIFY(v2[1] == 12);
		VERIFY(v2[2] == 13);
		VERIFY(v2[3] == 14);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace swap_test

}	// namespace hamon_vector_test
