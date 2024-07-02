/**
 *	@file	unit_test_deque_crbegin_crend.cpp
 *
 *	@brief	crbegin, crend のテスト
 *
 *	const_reverse_iterator crbegin() const noexcept;
 *	const_reverse_iterator crend() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace crbegin_crend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using ConstReverseIterator = typename Deque::const_reverse_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().crbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().crbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().crend()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().crend()),
		ConstReverseIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().crbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().crbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque&>().crend()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().crend()), "");

	{
		Deque v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Deque const v;
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Deque v{1,2,3};
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}
	{
		Deque const v{11,12,13,14};
		auto it = v.crbegin();
		VERIFY(it == v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it != v.crend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.crbegin());
		VERIFY(it == v.crend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CRBeginCREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace crbegin_crend_test

}	// namespace hamon_deque_test
