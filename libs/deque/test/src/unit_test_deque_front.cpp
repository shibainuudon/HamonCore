/**
 *	@file	unit_test_deque_front.cpp
 *
 *	@brief	front のテスト
 *
 *	reference       front();
 *	const_reference front() const;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace front_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using Reference = typename Deque::reference;
	using ConstReference = typename Deque::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().front()),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().front()),
		ConstReference
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().front()), "");
	static_assert(!noexcept(
		hamon::declval<Deque const&>().front()), "");
#endif

	{
		Deque v{1,2,3};
		VERIFY(v.front() == 1);

		v.front() = 42;

		VERIFY(v[0] == 42);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}
	{
		Deque const v{1,2,3};
		VERIFY(v.front() == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, FrontTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace front_test

}	// namespace hamon_deque_test
