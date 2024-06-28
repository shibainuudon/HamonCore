/**
 *	@file	unit_test_deque_at.cpp
 *
 *	@brief	at のテスト
 *
 *	reference       at(size_type n);
 *	const_reference at(size_type n) const;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace at_test
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
		decltype(hamon::declval<Deque&>().at(hamon::declval<SizeType>())),
		Reference
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().at(hamon::declval<SizeType>())),
		ConstReference
	>::value, "");

	static_assert(!noexcept(
		hamon::declval<Deque&>().at(hamon::declval<SizeType>())), "");
	static_assert(!noexcept(
		hamon::declval<Deque const&>().at(hamon::declval<SizeType>())), "");

	{
		Deque v{1,2,3};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);

		v.at(0) = 10;
		v.at(2) = 20;

		VERIFY(v.at(0) == 10);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 20);
	}
	{
		Deque const v{1,2,3};
		VERIFY(v.at(0) == 1);
		VERIFY(v.at(1) == 2);
		VERIFY(v.at(2) == 3);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, AtTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());

	{
		hamon::deque<int> v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
	{
		hamon::deque<int> const v{1,2,3};
		EXPECT_EQ(1, v.at(0));
		EXPECT_EQ(2, v.at(1));
		EXPECT_EQ(3, v.at(2));
#if !defined(HAMON_NO_EXCEPTIONS)
		EXPECT_THROW((void)v.at(3), hamon::out_of_range);
#endif
	}
}

}	// namespace at_test

}	// namespace hamon_deque_test
