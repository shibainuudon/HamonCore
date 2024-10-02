/**
 *	@file	unit_test_algorithm_ranges_count.cpp
 *
 *	@brief	ranges::count のテスト
 */

#include <hamon/algorithm/ranges/count.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 4,3,1,4,1,4,5,9,4,2,6,5,5,4, };

	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 0) == 0);
	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 1) == 2);
	VERIFY(ranges::count(ranges::begin(x), ranges::end(x), 2) == 1);
	VERIFY(ranges::count(x, 3) == 1);
	VERIFY(ranges::count(x, 4) == 5);
	VERIFY(ranges::count(x, 5) == 3);
	VERIFY(ranges::count(x, 6) == 1);
	VERIFY(ranges::count(x, 7) == 0);

	return true;
}

struct X { int i; };

inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	X x[] = { {2}, {2}, {6}, {8}, {10}, {11}, {2} };
	auto res = ranges::count(x, x+7, 2, &X::i);
	VERIFY(res == 3);
	res = ranges::count(x, x+7, 8, &X::i);
	VERIFY(res == 1);
	res = ranges::count(x, x+7, 9, &X::i);
	VERIFY(res == 0);

	test_forward_range<X> c(x);
	res = ranges::count(c, 6, &X::i);
	VERIFY(res == 1);
	res = ranges::count(c, 9, &X::i);
	VERIFY(res == 0);

	test_input_range<X> r(x);
	res = ranges::count(r, 2, &X::i);
	VERIFY(res == 3);

	test_input_range<X> r2(x);
	res = ranges::count(r2, 9, &X::i);
	VERIFY(res == 0);

	return true;
}

struct Y { int i; int j; };

inline HAMON_CXX11_CONSTEXPR bool
operator==(Y const& lhs, Y const& rhs)
{
	return lhs.i == rhs.i && lhs.j == rhs.j;
}
inline HAMON_CXX11_CONSTEXPR bool
operator!=(Y const& lhs, Y const& rhs)
{
	return !(lhs == rhs);
}

inline HAMON_CXX14_CONSTEXPR bool test03()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6}, {1,6} };
	VERIFY(ranges::count(y, 6, &Y::j) == 2);
	VERIFY(ranges::count(y, 5, &Y::j) == 0);

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test04()
{
	namespace ranges = hamon::ranges;

	Y y[] = { {1,2}, {2,4}, {3,6}, {1,6} };

	VERIFY(ranges::count(ranges::begin(y), ranges::end(y), {1,2}) == 1);
	VERIFY(ranges::count(ranges::begin(y), ranges::end(y), {1,4}) == 0);

	VERIFY(ranges::count(y, {1,2}) == 1);
	VERIFY(ranges::count(y, {1,4}) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCountTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
#if defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 100000)
	EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
#else
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
#endif
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace ranges_count_test

}	// namespace hamon_algorithm_test
