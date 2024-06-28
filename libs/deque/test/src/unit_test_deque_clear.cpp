/**
 *	@file	unit_test_deque_clear.cpp
 *
 *	@brief	clear のテスト
 *
 *	void clear() noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace clear_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().clear()),
		void
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().clear()), "");

	{
		Deque v{1,2,3};
		VERIFY(v.size() == 3);
		v.clear();
		VERIFY(v.size() == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, ClearTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace clear_test

}	// namespace hamon_deque_test
