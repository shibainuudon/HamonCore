/**
 *	@file	unit_test_deque_cbegin_cend.cpp
 *
 *	@brief	cbegin, cend のテスト
 *
 *	const_iterator         cbegin() const noexcept;
 *	const_iterator         cend() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace cbegin_cend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().cbegin()),
		ConstIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().cbegin()),
		ConstIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().cend()),
		ConstIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().cend()),
		ConstIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().cbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().cbegin()), "");
	static_assert(noexcept(
		hamon::declval<Deque&>().cend()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().cend()), "");

	{
		Deque v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Deque const v;
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Deque v{1,2,3};
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	{
		Deque const v{11,12,13,14};
		auto it = v.cbegin();
		VERIFY(it == v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it != v.cend());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.cbegin());
		VERIFY(it == v.cend());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, CBeginCEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace cbegin_cend_test

}	// namespace hamon_deque_test
