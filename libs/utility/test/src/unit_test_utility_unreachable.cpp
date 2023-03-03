/**
 *	@file	unit_test_utility_unreachable.cpp
 *
 *	@brief	unreachable のテスト
 */

#include <hamon/utility/unreachable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_utility_test
{

namespace unreachable_test
{

HAMON_CXX14_CONSTEXPR int flip(int x)
{
	switch (x)
	{
	case 0:
		return 1;
	case 1:
		return 0;
	default:
		// C++コンパイラは引数 x が値0,1以外を取らないと
		// 仮定したコード生成を行う可能性がある。
		hamon::unreachable();
	}
}

GTEST_TEST(UtilityTest, UnreachableTest)
{
	HAMON_CXX14_CONSTEXPR auto x = flip(0);
	HAMON_CXX14_CONSTEXPR auto y = flip(1);
	(void)x;
	(void)y;

//	static_assert(noexcept(hamon::unreachable()), "");
	static_assert(hamon::is_same<decltype(hamon::unreachable()), void>::value, "");
}

}	// namespace unreachable_test

}	// namespace hamon_utility_test
