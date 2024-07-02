/**
 *	@file	unit_test_deque_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *  void swap(deque&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value);
 *
 *  template<class T, class Allocator>
 *	void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().swap(hamon::declval<Deque&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(swap(hamon::declval<Deque&>(), hamon::declval<Deque&>())),
		void
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().swap(hamon::declval<Deque&>())), "");
	static_assert(noexcept(
		swap(hamon::declval<Deque&>(), hamon::declval<Deque&>())), "");

	{
		Deque v1 {1,2,3};
		Deque v2 {11,12,13,14};
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

GTEST_TEST(DequeTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<double>());
}

}	// namespace swap_test

}	// namespace hamon_deque_test
