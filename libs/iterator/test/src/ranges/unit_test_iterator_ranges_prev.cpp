/**
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

void test01()
{
	static HAMON_CXX11_CONSTEXPR int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	HAMON_CXX11_CONSTEXPR test_random_access_range<int const> r(a);
	HAMON_CXX11_CONSTEXPR auto begin = r.begin();
	HAMON_CXX11_CONSTEXPR auto end = r.end();
	HAMON_CXX11_CONSTEXPR auto endi = hamon::ranges::next(begin, end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi) == 9);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 1) == 9);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 3) == 7);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(begin, -4) == 4);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 5, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, -5, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0, endi) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 5, begin) == 5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 55, begin) == begin);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 0, endi) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, -5, endi) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, -55, endi) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 0, begin) == end);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(begin, -5, endi) == 5);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, -55, endi) == end);
}

void test02()
{
	static HAMON_CXX14_CONSTEXPR int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	HAMON_CXX14_CONSTEXPR test_bidirectional_range<int const> r(a);
	HAMON_CXX14_CONSTEXPR auto begin = r.begin();
	HAMON_CXX14_CONSTEXPR auto end = r.end();
	HAMON_CXX14_CONSTEXPR auto endi = hamon::ranges::next(begin, end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi) == 9);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 1) == 9);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 3) == 7);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(begin, -4) == 4);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 5, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, -5, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, 0, endi) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(endi, 5, begin) == 5);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 55, begin) == begin);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 0, endi) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, -5, endi) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, -55, endi) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(endi, 0, begin) == end);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(*hamon::ranges::prev(begin, -5, endi) == 5);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE( hamon::ranges::prev(begin, -55, endi) == end);
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
	test01();
	test02();
}

}	// namespace ranges_prev_test

}	// namespace hamon_iterator_test
