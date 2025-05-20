/**
 *	@file	unit_test_unexpected_swap_member.cpp
 *
 *	@brief	swap() のテスト
 *
 *	constexpr void swap(unexpected& other) noexcept(see below);
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace swap_member_test
{

template <typename E, typename = void>
struct HasMemberSwap
	: hamon::false_type{};

template <typename E>
struct HasMemberSwap<E, hamon::void_t<decltype(
	hamon::declval<hamon::unexpected<E>&>().swap(hamon::declval<hamon::unexpected<E>&>()))>>
	: hamon::true_type{};

struct NonSwappable
{
	friend void swap(NonSwappable&, NonSwappable&) = delete;
};

struct Swappable
{
	friend void swap(Swappable&, Swappable&);
};

struct NoThrowSwappable
{
	friend void swap(NoThrowSwappable&, NoThrowSwappable&) noexcept;
};

#if !defined(HAMON_USE_STD_EXPECTED)
static_assert(HasMemberSwap<NonSwappable>::value, "");
#endif
static_assert(HasMemberSwap<Swappable>::value, "");
static_assert(HasMemberSwap<NoThrowSwappable>::value, "");

template <typename E>
struct MemberSwapNoexcept : hamon::bool_constant<noexcept(
	hamon::declval<hamon::unexpected<E>&>().swap(hamon::declval<hamon::unexpected<E>&>()))>{};

static_assert(!MemberSwapNoexcept<Swappable>::value, "");
static_assert( MemberSwapNoexcept<NoThrowSwappable>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::unexpected<E> unex1(E{5});
		hamon::unexpected<E> unex2(E{6});
		unex1.swap(unex2);
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
		unex1.swap(unex2);
		VERIFY(unex1.error().i == 11);
		VERIFY(unex2.error().i == 10);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, SwapMemberTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test2()));
}

}	// namespace swap_member_test

}	// namespace hamon_unexpected_test
