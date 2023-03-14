/**
 *	@file	unit_test_array_swap.cpp
 *
 *	@brief	constexpr void swap(array&) のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_array_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct NonSwappable
{
	HAMON_CXX11_CONSTEXPR NonSwappable() {}
private:
	NonSwappable(NonSwappable const&) = delete;
	NonSwappable& operator=(NonSwappable const&) = delete;
};

struct MayThrowSwappable
{
	HAMON_CXX11_CONSTEXPR MayThrowSwappable() {}
	HAMON_CXX11_CONSTEXPR MayThrowSwappable(MayThrowSwappable const&) {}
	HAMON_CXX14_CONSTEXPR MayThrowSwappable& operator=(MayThrowSwappable const&) {return *this;}
};

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool SwapTest()
{
	{
		using Array = hamon::array<T, 3>;
		Array a1{T(1), T(2), T(3)};
		Array a2{T(4), T(5), T(6)};
	
		a1.swap(a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(a1.swap(a2));
		
		VERIFY(a1[0] == T(4));
		VERIFY(a1[1] == T(5));
		VERIFY(a1[2] == T(6));
		VERIFY(a2[0] == T(1));
		VERIFY(a2[1] == T(2));
		VERIFY(a2[2] == T(3));
		
		using std::swap;
		swap(a1, a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(swap(a1, a2));
		
		VERIFY(a1[0] == T(1));
		VERIFY(a1[1] == T(2));
		VERIFY(a1[2] == T(3));
		VERIFY(a2[0] == T(4));
		VERIFY(a2[1] == T(5));
		VERIFY(a2[2] == T(6));
	}
	{
		using Array = hamon::array<T, 0>;
		Array a1{};
		Array a2{};
		
		a1.swap(a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(a1.swap(a2));
		
		VERIFY(a1.size() == 0);
		VERIFY(a2.size() == 0);
		
		using std::swap;
		swap(a1, a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(swap(a1, a2));

		VERIFY(a1.size() == 0);
		VERIFY(a2.size() == 0);
	}

	return true;
}

GTEST_TEST(ArrayTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SwapTest<double>());

#if !defined(HAMON_USE_STD_ARRAY)
	{
		using Array = hamon::array<NonSwappable, 0>;
		Array a1{};
		Array a2{};

		a1.swap(a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(a1.swap(a2));

		EXPECT_TRUE(a1.size() == 0);
		EXPECT_TRUE(a2.size() == 0);

		using std::swap;
		swap(a1, a2);
		HAMON_ASSERT_NOEXCEPT_TRUE(swap(a1, a2));

		EXPECT_TRUE(a1.size() == 0);
		EXPECT_TRUE(a2.size() == 0);
	}
#endif
	{
		using std::swap;
		using Array = hamon::array<NonSwappable, 1>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<Array&>().swap(hamon::declval<Array&>()));
//		HAMON_ASSERT_NOEXCEPT_FALSE(swap(hamon::declval<Array&>(), hamon::declval<Array&>()));
	}
	{
		using std::swap;
		using Array = hamon::array<MayThrowSwappable, 0>;
		HAMON_ASSERT_NOEXCEPT_TRUE(hamon::declval<Array&>().swap(hamon::declval<Array&>()));
		HAMON_ASSERT_NOEXCEPT_TRUE(swap(hamon::declval<Array&>(), hamon::declval<Array&>()));
	}
	{
		using std::swap;
		using Array = hamon::array<MayThrowSwappable, 1>;
		HAMON_ASSERT_NOEXCEPT_FALSE(hamon::declval<Array&>().swap(hamon::declval<Array&>()));
		HAMON_ASSERT_NOEXCEPT_FALSE(swap(hamon::declval<Array&>(), hamon::declval<Array&>()));
	}
}

}	// namespace swap_test

}	// namespace hamon_array_test
