/**
 *	@file	unit_test_unexpected_swap_free.cpp
 *
 *	@brief	swap() のテスト
 *
 *	friend constexpr void swap(unexpected& x, unexpected& y) noexcept(noexcept(x.swap(y)));
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/is_swappable.hpp>
#include <hamon/type_traits/is_nothrow_swappable.hpp>
#include <hamon/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace swap_free_test
{

struct NonSwappable
{
	NonSwappable& operator=(const NonSwappable&) = delete;
};

struct Swappable
{
	friend void swap(Swappable&, Swappable&);
};

struct NoThrowSwappable
{
	friend void swap(NoThrowSwappable&, NoThrowSwappable&) noexcept;
};

static_assert(!hamon::is_swappable<hamon::unexpected<NonSwappable>>::value, "");
static_assert( hamon::is_swappable<hamon::unexpected<Swappable>>::value, "");
static_assert( hamon::is_swappable<hamon::unexpected<NoThrowSwappable>>::value, "");

static_assert(!hamon::is_nothrow_swappable<hamon::unexpected<NonSwappable>>::value, "");
static_assert(!hamon::is_nothrow_swappable<hamon::unexpected<Swappable>>::value, "");
static_assert( hamon::is_nothrow_swappable<hamon::unexpected<NoThrowSwappable>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::unexpected<E> unex1(E{5});
		hamon::unexpected<E> unex2(E{6});
		swap(unex1, unex2);
		VERIFY(unex1.error() == E{6});
		VERIFY(unex2.error() == E{5});
	}
	return true;
}

struct ADLSwap
{
	constexpr ADLSwap(int ii) : i(ii) {}
	ADLSwap& operator=(const ADLSwap&) = delete;
	int i;
	HAMON_CXX14_CONSTEXPR friend void swap(ADLSwap& x, ADLSwap& y) { hamon::swap(x.i, y.i); }
};

HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		hamon::unexpected<ADLSwap> unex1(10);
		hamon::unexpected<ADLSwap> unex2(11);
		swap(unex1, unex2);
		VERIFY(unex1.error().i == 11);
		VERIFY(unex2.error().i == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, SwapFreeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace swap_free_test

}	// namespace hamon_unexpected_test
