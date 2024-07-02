/**
 *	@file	unit_test_deque_rbegin_rend.cpp
 *
 *	@brief	rbegin, rend のテスト
 *
 *	reverse_iterator       rbegin() noexcept;
 *	const_reverse_iterator rbegin() const noexcept;
 *	reverse_iterator       rend() noexcept;
 *	const_reverse_iterator rend() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace rbegin_rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using ReverseIterator = typename Deque::reverse_iterator;
	using ConstReverseIterator = typename Deque::const_reverse_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().rbegin()),
		ReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().rbegin()),
		ConstReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().rend()),
		ReverseIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().rend()),
		ConstReverseIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().rbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().rbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque&>().rend()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().rend()), "");

	{
		Deque v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Deque const v;
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Deque v{1,2,3};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	{
		Deque const v{11,12,13,14};
		auto it = v.rbegin();
		VERIFY(it == v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it != v.rend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.rbegin());
		VERIFY(it == v.rend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, RBeginREndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace rbegin_rend_test

}	// namespace hamon_deque_test
