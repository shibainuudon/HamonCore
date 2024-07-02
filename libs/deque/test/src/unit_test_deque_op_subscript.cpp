/**
 *	@file	unit_test_deque_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	reference       operator[](size_type n);
 *	const_reference operator[](size_type n) const;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace op_subscript_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using SizeType = typename Deque::size_type;
	using Reference = typename Deque::reference;
	using ConstReference = typename Deque::const_reference;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>()[hamon::declval<SizeType>()]),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>()[hamon::declval<SizeType>()]),
		ConstReference
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>()[hamon::declval<SizeType>()]), "");
	static_assert(!noexcept(
		hamon::declval<Deque const&>()[hamon::declval<SizeType>()]), "");
#endif

	{
		Deque v{1,2,3};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);

		v[0] = 10;
		v[2] = 20;

		VERIFY(v[0] == 10);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 20);
	}
	{
		Deque const v{1,2,3};
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, OpSubscriptTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_subscript_test

}	// namespace hamon_deque_test
