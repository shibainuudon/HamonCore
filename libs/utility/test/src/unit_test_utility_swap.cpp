/**
 *	@file	unit_test_utility_swap.cpp
 *
 *	@brief	swap のテスト
 */

#include <hamon/utility/swap.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include "constexpr_test.hpp"

namespace hamon_utility_test
{

namespace swap_test
{

struct CopyOnly
{
	CopyOnly() {}
	CopyOnly(CopyOnly const&) noexcept {}
	CopyOnly& operator=(CopyOnly const&) { return *this; }
};

struct MoveOnly
{
	MoveOnly() {}
	MoveOnly(MoveOnly&&) {}
	MoveOnly& operator=(MoveOnly&&) noexcept { return *this; }
};

struct NoexceptMoveOnly
{
	NoexceptMoveOnly() {}
	NoexceptMoveOnly(NoexceptMoveOnly&&) noexcept {}
	NoexceptMoveOnly& operator=(NoexceptMoveOnly&&) noexcept { return *this; }
};

struct NotMoveConstructible
{
	NotMoveConstructible& operator=(NotMoveConstructible&&) { return *this; }
private:
	NotMoveConstructible(NotMoveConstructible&&);
};

struct NotMoveAssignable
{
	NotMoveAssignable(NotMoveAssignable&&);
private:
	NotMoveAssignable& operator=(NotMoveAssignable&&);
};

template <typename T>
using invoke_swap = decltype(hamon::swap(hamon::declval<T>(), hamon::declval<T>()));

static_assert(!hamon::is_detected<invoke_swap, int>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int*>::value, "");
static_assert( hamon::is_detected<invoke_swap, int&>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int&&>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const*>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const&>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const&&>::value, "");
static_assert( hamon::is_detected<invoke_swap, CopyOnly&>::value, "");
static_assert( hamon::is_detected<invoke_swap, MoveOnly&>::value, "");
static_assert( hamon::is_detected<invoke_swap, NoexceptMoveOnly&>::value, "");
static_assert(!hamon::is_detected<invoke_swap, NotMoveConstructible&>::value, "");
static_assert(!hamon::is_detected<invoke_swap, NotMoveAssignable&>::value, "");

static_assert(!hamon::is_detected<invoke_swap, int[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int(*)[2]>::value, "");
static_assert( hamon::is_detected<invoke_swap, int(&)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int(&&)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const(*)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const(&)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, int const(&&)[2]>::value, "");
static_assert( hamon::is_detected<invoke_swap, CopyOnly(&)[2]>::value, "");
static_assert( hamon::is_detected<invoke_swap, MoveOnly(&)[2]>::value, "");
static_assert( hamon::is_detected<invoke_swap, NoexceptMoveOnly(&)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, NotMoveConstructible(&)[2]>::value, "");
static_assert(!hamon::is_detected<invoke_swap, NotMoveAssignable(&)[2]>::value, "");

static_assert( noexcept(hamon::swap(hamon::declval<int&>(), hamon::declval<int&>())), "");
static_assert(!noexcept(hamon::swap(hamon::declval<CopyOnly&>(), hamon::declval<CopyOnly&>())), "");
static_assert(!noexcept(hamon::swap(hamon::declval<MoveOnly&>(), hamon::declval<MoveOnly&>())), "");
static_assert( noexcept(hamon::swap(hamon::declval<NoexceptMoveOnly&>(), hamon::declval<NoexceptMoveOnly&>())), "");

static_assert( noexcept(hamon::swap(hamon::declval<int(&)[2]>(), hamon::declval<int(&)[2]>())), "");
static_assert(!noexcept(hamon::swap(hamon::declval<CopyOnly(&)[2]>(), hamon::declval<CopyOnly(&)[2]>())), "");
static_assert(!noexcept(hamon::swap(hamon::declval<MoveOnly(&)[2]>(), hamon::declval<MoveOnly(&)[2]>())), "");
static_assert( noexcept(hamon::swap(hamon::declval<NoexceptMoveOnly(&)[2]>(), hamon::declval<NoexceptMoveOnly(&)[2]>())), "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		int i = 1;
		int j = 2;
		hamon::swap(i, j);
		VERIFY(i == 2);
		VERIFY(j == 1);
	}
	{
		int i[3] = {1, 2, 3};
		int j[3] = {4, 5, 6};
		hamon::swap(i, j);
		VERIFY(i[0] == 4);
		VERIFY(i[1] == 5);
		VERIFY(i[2] == 6);
		VERIFY(j[0] == 1);
		VERIFY(j[1] == 2);
		VERIFY(j[2] == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UtilityTest, SwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));
}

}	// namespace swap_test

}	// namespace hamon_utility_test
