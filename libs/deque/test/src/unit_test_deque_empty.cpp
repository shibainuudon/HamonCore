﻿/**
 *	@file	unit_test_deque_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	[[nodiscard]] bool empty() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace empty_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().empty()),
		bool
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().empty()), "");

	{
		Deque v;
		VERIFY(v.empty());
		v.push_back(1);
		VERIFY(!v.empty());
		v.clear();
		VERIFY(v.empty());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, EmptyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace empty_test

}	// namespace hamon_deque_test
