﻿/**
 *	@file	unit_test_deque_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	size_type max_size() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace max_size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using SizeType = typename Deque::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().max_size()),
		SizeType
	>::value, "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().max_size()), "");

	{
		Deque const v;
		VERIFY(v.max_size() > 0);
	}
	{
		Deque const v{1,3,4};
		VERIFY(v.max_size() > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, MaxSizeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace max_size_test

}	// namespace hamon_deque_test
