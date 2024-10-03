﻿/**
 *	@file	unit_test_deque_erase.cpp
 *
 *	@brief	erase のテスト
 *
 *	iterator erase(const_iterator position);
 *	iterator erase(const_iterator first, const_iterator last);
 *
 *	template<class T, class Allocator, class U = T>
 *	constexpr typename deque<T, Allocator>::size_type
 *	erase(deque<T, Allocator>& c, const U& value);
 */

#include <hamon/deque.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace erase_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX20_CONSTEXPR bool test1()
{
	using T = int;
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().erase(hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().erase(hamon::declval<ConstIterator>())), "");
#endif

	{
		Deque v {1,2,3,4,5};
		auto ret = v.erase(v.begin());
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 2);
		VERIFY(v[1] == 3);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 5);
	}
	{
		Deque v {1,2,3,4,5};
		auto ret = v.erase(v.begin() + 2);
		VERIFY(ret == v.begin() + 2);
		VERIFY(v.size() == 4);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 2);
		VERIFY(v[2] == 4);
		VERIFY(v[3] == 5);
	}

	return true;
}

HAMON_CXX20_CONSTEXPR bool test2()
{
	using T = int;
	using Deque = hamon::deque<T>;
	using Iterator = typename Deque::iterator;
	using ConstIterator = typename Deque::const_iterator;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())),
		Iterator
	>::value, "");

#if 0
	static_assert(!noexcept(
		hamon::declval<Deque&>().erase(hamon::declval<ConstIterator>(), hamon::declval<ConstIterator>())), "");
#endif

	{
		Deque v {1,2,3,4,5};
		auto ret = v.erase(v.begin() + 1, v.begin() + 3);
		VERIFY(ret == v.begin() + 1);
		VERIFY(v.size() == 3);
		VERIFY(v[0] == 1);
		VERIFY(v[1] == 4);
		VERIFY(v[2] == 5);
	}
	{
		Deque v {1,2,3,4,5};
		auto ret = v.erase(v.begin(), v.end());
		VERIFY(ret == v.begin());
		VERIFY(v.size() == 0);
	}
	return true;
}

HAMON_CXX20_CONSTEXPR bool test3()
{
	using T = int;
	using Deque = hamon::deque<T>;
	using SizeType = typename Deque::size_type;

	static_assert(hamon::is_same<
		decltype(hamon::erase(hamon::declval<Deque&>(), hamon::declval<T const&>())),
		SizeType
	>::value, "");

	static_assert(!noexcept(
		hamon::erase(hamon::declval<Deque&>(), hamon::declval<T const&>())), "");

	{
		Deque v = {3,1,4,5,2};
		auto r = hamon::erase(v, 1);
		VERIFY(r == 1);
		const T v2[] = {3,4,5,2,};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	{
		Deque v = {9,1,9,9,2,3,9,9,9,4,5,9,9,9,9,};
		auto r = hamon::erase(v, 9);
		VERIFY(r == 10);
		const T v2[] = {1,2,3,4,5};
		VERIFY(hamon::ranges::equal(v, v2));
	}
	return true;
}

struct Point
{
	int x;
	int y;
};

inline HAMON_CXX11_CONSTEXPR bool
operator==(Point const& lhs, Point const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

HAMON_CXX20_CONSTEXPR bool test4()
{
	hamon::deque<Point> d;
	d.push_back(Point{1,2});
	d.push_back(Point{2,3});
	d.push_back(Point{1,3});
	d.push_back(Point{1,2});
	d.push_back(Point{3,2});
	auto r = hamon::erase(d, {1,2});
	VERIFY(r == 2);
	VERIFY(d.size() == 3);
	VERIFY(d[0] == Point{2,3});
	VERIFY(d[1] == Point{1,3});
	VERIFY(d[2] == Point{3,2});
	return true;
}

#undef VERIFY

GTEST_TEST(DequeTest, EraseTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test2());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test3());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test4());
}

}	// namespace erase_test

}	// namespace hamon_deque_test
