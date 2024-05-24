/**
 *	@file	unit_test_memory_addressof.cpp
 *
 *	@brief	addressof のテスト
 */

#include <hamon/memory/addressof.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace addressof_test
{

struct UselessType {};

// operator&がオーバーロードされていないクラス
struct A
{
};

// operator&がオーバーロードされているクラス
struct B
{
	HAMON_CONSTEXPR UselessType operator&(void) const
	{
		return UselessType();
	}
};

// operator&がグローバル関数としてオーバーロードされているクラス
struct C
{
};

HAMON_CONSTEXPR UselessType operator&(C const&)
{
	return UselessType();
}

HAMON_CONSTEXPR int func(UselessType)
{
	return 0;
}

HAMON_CONSTEXPR int func(A const*)
{
	return 1;
}

HAMON_CONSTEXPR int func(B const*)
{
	return 2;
}

HAMON_CONSTEXPR int func(C const*)
{
	return 3;
}

GTEST_TEST(MemoryTest, AddressofTest)
{
	{
		HAMON_CONSTEXPR int n1 = 0;
		HAMON_CONSTEXPR const int n2 = 0;
		volatile int n3 = 0;
		const volatile int n4 = 0;
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(&n1 == hamon::addressof(n1));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(&n2 == hamon::addressof(n2));
		EXPECT_TRUE(&n3 == hamon::addressof(n3));
		EXPECT_TRUE(&n4 == hamon::addressof(n4));
	}
	{
		HAMON_CONSTEXPR A a {};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, func(&a));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1, func(hamon::addressof(a)));
	}
	{
		HAMON_CONSTEXPR B b {};
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(0, func(&b));
#if defined(HAMON_USE_STD_ADDRESSOF)
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(2, func(hamon::addressof(b)));
#else
		                      EXPECT_EQ(2, func(hamon::addressof(b)));
#endif
	}
	{
		HAMON_CONSTEXPR C c {};
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(0, func(&c));
#if defined(HAMON_USE_STD_ADDRESSOF)
		HAMON_CXX17_CONSTEXPR_EXPECT_EQ(3, func(hamon::addressof(c)));
#else
		                      EXPECT_EQ(3, func(hamon::addressof(c)));
#endif
	}
}

}	// namespace addressof_test

}	// namespace hamon_memory_test
