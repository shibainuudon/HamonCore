/**
 *	@file	unit_test_memory_unique_ptr_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(unique_ptr& u) noexcept;
 *
 *	template<class T, class D>
 *	constexpr void swap(unique_ptr<T, D>& x, unique_ptr<T, D>& y) noexcept;
 */

#include <hamon/memory/unique_ptr.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace swap_test
{

struct D1
{
	int value;

	HAMON_CXX11_CONSTEXPR D1(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete p; }
};

struct D2
{
	int value;

	HAMON_CXX11_CONSTEXPR D2(int v) : value(v) {}

	template <typename T>
	HAMON_CXX14_CONSTEXPR void operator()(T* p) const { delete[] p; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR
bool test()
{
	{
		hamon::unique_ptr<int, D1> up1(new int{10}, D1{11});
		hamon::unique_ptr<int, D1> up2(new int{12}, D1{13});
		VERIFY(*up1 == 10);
		VERIFY(up1.get_deleter().value == 11);
		VERIFY(*up2 == 12);
		VERIFY(up2.get_deleter().value == 13);
		up1.swap(up2);
		VERIFY(*up1 == 12);
		VERIFY(up1.get_deleter().value == 13);
		VERIFY(*up2 == 10);
		VERIFY(up2.get_deleter().value == 11);
		swap(up1, up2);
		VERIFY(*up1 == 10);
		VERIFY(up1.get_deleter().value == 11);
		VERIFY(*up2 == 12);
		VERIFY(up2.get_deleter().value == 13);
	}
	{
		hamon::unique_ptr<int[], D2> up1(new int[]{1,2,3}, D2{20});
		hamon::unique_ptr<int[], D2> up2(new int[]{4,5}, D2{30});
		VERIFY(up1[0] == 1);
		VERIFY(up1[1] == 2);
		VERIFY(up1[2] == 3);
		VERIFY(up1.get_deleter().value == 20);
		VERIFY(up2[0] == 4);
		VERIFY(up2[1] == 5);
		VERIFY(up2.get_deleter().value == 30);
		up1.swap(up2);
		VERIFY(up1[0] == 4);
		VERIFY(up1[1] == 5);
		VERIFY(up1.get_deleter().value == 30);
		VERIFY(up2[0] == 1);
		VERIFY(up2[1] == 2);
		VERIFY(up2[2] == 3);
		VERIFY(up2.get_deleter().value == 20);
		swap(up1, up2);
		VERIFY(up1[0] == 1);
		VERIFY(up1[1] == 2);
		VERIFY(up1[2] == 3);
		VERIFY(up1.get_deleter().value == 20);
		VERIFY(up2[0] == 4);
		VERIFY(up2[1] == 5);
		VERIFY(up2.get_deleter().value == 30);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UniquePtrTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test());

	{
		using UP = hamon::unique_ptr<int>;
		static_assert( hamon::is_same<void, decltype(hamon::declval<UP&>().swap(hamon::declval<UP&>()))>::value, "");
		static_assert( noexcept(hamon::declval<UP&>().swap(hamon::declval<UP&>())), "");
		static_assert( hamon::is_same<void, decltype(swap(hamon::declval<UP&>(), hamon::declval<UP&>()))>::value, "");
		static_assert( noexcept(swap(hamon::declval<UP&>(), hamon::declval<UP&>())), "");
	}
	{
		using UP = hamon::unique_ptr<int[]>;
		static_assert( hamon::is_same<void, decltype(hamon::declval<UP&>().swap(hamon::declval<UP&>()))>::value, "");
		static_assert( noexcept(hamon::declval<UP&>().swap(hamon::declval<UP&>())), "");
		static_assert( hamon::is_same<void, decltype(swap(hamon::declval<UP&>(), hamon::declval<UP&>()))>::value, "");
		static_assert( noexcept(swap(hamon::declval<UP&>(), hamon::declval<UP&>())), "");
	}
}

}	// namespace swap_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
