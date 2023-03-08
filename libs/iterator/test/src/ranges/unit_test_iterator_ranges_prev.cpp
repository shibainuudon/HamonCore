﻿/**
 *	@file	unit_test_iterator_ranges_prev.cpp
 *
 *	@brief	ranges::prev のテスト
 */

#include <hamon/iterator/ranges/prev.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test
{

namespace ranges_prev_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_random_access_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = hamon::ranges::next(begin, end);
	VERIFY(*hamon::ranges::prev(endi) == 9);
	VERIFY( hamon::ranges::prev(begin, 0) == begin);
	VERIFY(*hamon::ranges::prev(endi, 1) == 9);
	VERIFY(*hamon::ranges::prev(endi, 3) == 7);
	VERIFY(*hamon::ranges::prev(begin, -4) == 4);
	VERIFY( hamon::ranges::prev(begin, 0, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, 5, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, -5, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, 0, endi) == begin);
	VERIFY(*hamon::ranges::prev(endi, 5, begin) == 5);
	VERIFY( hamon::ranges::prev(endi, 55, begin) == begin);
	VERIFY( hamon::ranges::prev(endi, 0, endi) == end);
	VERIFY( hamon::ranges::prev(endi, -5, endi) == end);
	VERIFY( hamon::ranges::prev(endi, -55, endi) == end);
	VERIFY( hamon::ranges::prev(endi, 0, begin) == end);
	VERIFY(*hamon::ranges::prev(begin, -5, endi) == 5);
	VERIFY( hamon::ranges::prev(begin, -55, endi) == end);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	test_bidirectional_range<int> r(a);
	auto begin = r.begin();
	auto end = r.end();
	auto endi = hamon::ranges::next(begin, end);
	VERIFY(*hamon::ranges::prev(endi) == 9);
	VERIFY( hamon::ranges::prev(begin, 0) == begin);
	VERIFY(*hamon::ranges::prev(endi, 1) == 9);
	VERIFY(*hamon::ranges::prev(endi, 3) == 7);
	VERIFY(*hamon::ranges::prev(begin, -4) == 4);
	VERIFY( hamon::ranges::prev(begin, 0, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, 5, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, -5, begin) == begin);
	VERIFY( hamon::ranges::prev(begin, 0, endi) == begin);
	VERIFY(*hamon::ranges::prev(endi, 5, begin) == 5);
	VERIFY( hamon::ranges::prev(endi, 55, begin) == begin);
	VERIFY( hamon::ranges::prev(endi, 0, endi) == end);
	VERIFY( hamon::ranges::prev(endi, -5, endi) == end);
	VERIFY( hamon::ranges::prev(endi, -55, endi) == end);
	VERIFY( hamon::ranges::prev(endi, 0, begin) == end);
	VERIFY(*hamon::ranges::prev(begin, -5, endi) == 5);
	VERIFY( hamon::ranges::prev(begin, -55, endi) == end);

	return true;
}

#undef VERIFY

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept can_prev =
	requires(T& t) { hamon::ranges::prev(t); } &&
	requires(T& t) { hamon::ranges::prev(t, 1); } &&
	requires(T& t) { hamon::ranges::prev(t, 1, t); };

static_assert( can_prev<random_access_iterator_wrapper<int>>, "");
static_assert( can_prev<bidirectional_iterator_wrapper<int>>, "");
static_assert(!can_prev<forward_iterator_wrapper<int>>, "");
static_assert(!can_prev<input_iterator_wrapper<int>>, "");
static_assert(!can_prev<output_iterator_wrapper<int>>, "");

#else

template <typename T>
struct can_prev_impl
{
private:
	template <typename U>
	static auto test(int) -> decltype(
		hamon::ranges::prev(hamon::declval<U&>()),
		hamon::ranges::prev(hamon::declval<U&>(), 1),
		hamon::ranges::prev(hamon::declval<U&>(), 1, hamon::declval<U&>()),
		hamon::true_type{});

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using can_prev =
	typename can_prev_impl<T>::type;

static_assert( can_prev<random_access_iterator_wrapper<int>>::value, "");
static_assert( can_prev<bidirectional_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<forward_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<input_iterator_wrapper<int>>::value, "");
static_assert(!can_prev<output_iterator_wrapper<int>>::value, "");

#endif

GTEST_TEST(IteratorTest, RangesPrevTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ranges_prev_test

}	// namespace hamon_iterator_test
