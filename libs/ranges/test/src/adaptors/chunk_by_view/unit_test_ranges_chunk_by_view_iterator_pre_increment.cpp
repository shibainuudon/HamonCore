﻿/**
 *	@file	unit_test_ranges_chunk_by_view_iterator_pre_increment.cpp
 *
 *	@brief	前置インクリメントのテスト
 *
 *	constexpr iterator& operator++();
 */

#include <hamon/ranges/adaptors/chunk_by_view.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace chunk_by_view_test
{
namespace iterator_pre_increment_test
{

template <typename T, typename = void>
struct has_pre_increment
	: public hamon::false_type {};

template <typename T>
struct has_pre_increment<T, hamon::void_t<decltype(++hamon::declval<T>())>>
	: public hamon::true_type {};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_forward_view<int>;
	using F = hamon::ranges::less;
	using CV = hamon::ranges::chunk_by_view<V, F>;
	using I = decltype(hamon::declval<CV&>().begin());
	static_assert( has_pre_increment<I&>::value, "");
	static_assert(!has_pre_increment<I const&>::value, "");
	static_assert(hamon::is_same<decltype(++hamon::declval<I&>()), I&>::value, "");

	int a[] = {3,1,4,1,5,9};
	V v(a);
	CV cv(v, F{});
	auto it = cv.begin();
	{
		int expected[] = {3};
		VERIFY(hamon::ranges::equal(*it, expected));
	}
	auto& t1 = ++it;
	VERIFY(&t1 == &it);
	{
		int expected[] = {1,4};
		VERIFY(hamon::ranges::equal(*it, expected));
	}
	auto& t2 = ++it;
	VERIFY(&t2 == &it);
	{
		int expected[] = {1,5,9};
		VERIFY(hamon::ranges::equal(*it, expected));
	}
	VERIFY(it != cv.end());
	VERIFY(++it == cv.end());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ChunkByViewIteratorPreIncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iterator_pre_increment_test
}	// namespace chunk_by_view_test
}	// namespace hamon_ranges_test
