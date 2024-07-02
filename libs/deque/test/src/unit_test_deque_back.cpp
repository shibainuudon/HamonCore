/**
 *	@file	unit_test_deque_back.cpp
 *
 *	@brief	back のテスト
 *
 *	reference       back();
 *	const_reference back() const;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace back_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using Reference = typename Deque::reference;
	using ConstReference = typename Deque::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().back()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().back()),
		ConstReference
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().back()), "");
	static_assert(!noexcept(
		hamon::declval<Deque const&>().back()), "");
#endif

	{
		Deque v{1,2,3};
		VERIFY(v.back() == 3);

		v.back() = 42;

		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 42);
	}
	{
		Deque const v{1,2,3};
		VERIFY(v.back() == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, BackTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace back_test

}	// namespace hamon_deque_test
