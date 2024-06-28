/**
 *	@file	unit_test_deque_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	deque()
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace ctor_default_test
{

struct S1
{
	S1() = delete;
};

struct S2
{
	S2() {}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert( hamon::is_default_constructible<Deque>::value, "");
	static_assert(!hamon::is_nothrow_default_constructible<Deque>::value, "");
	static_assert( hamon::is_implicitly_default_constructible<Deque>::value, "");
	static_assert(!hamon::is_trivially_default_constructible<Deque>::value, "");

	{
		Deque v;
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Deque v{};
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}
	{
		Deque v = {};
		VERIFY(v.size() == 0);
		VERIFY(v.empty());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S1>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<S2>());
}

}	// namespace ctor_default_test

}	// namespace hamon_deque_test
