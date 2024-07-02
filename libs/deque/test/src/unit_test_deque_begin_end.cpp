/**
 *	@file	unit_test_deque_begin_end.cpp
 *
 *	@brief	begin, end のテスト
 *
 *	iterator               begin() noexcept;
 *	const_iterator         begin() const noexcept;
 *	iterator               end() noexcept;
 *	const_iterator         end() const noexcept;
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace begin_end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().begin()),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().begin()),
		ConstIterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().end()),
		Iterator
	>::value, "");
	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque const&>().end()),
		ConstIterator
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().begin()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().begin()), "");
	static_assert(noexcept(
		hamon::declval<Deque&>().end()), "");
	static_assert(noexcept(
		hamon::declval<Deque const&>().end()), "");

	{
		Deque v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Deque const v;
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it == v.end());
	}
	{
		Deque v{1,2,3};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 1);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 2);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 3);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	{
		Deque const v{11,12,13,14};
		auto it = v.begin();
		VERIFY(it == v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 11);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 12);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 13);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it != v.end());
		VERIFY(*it == 14);
		++it;
		VERIFY(it != v.begin());
		VERIFY(it == v.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, BeginEndTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<unsigned int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace begin_end_test

}	// namespace hamon_deque_test
