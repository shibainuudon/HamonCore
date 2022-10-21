/**
 *	@file	unit_test_algorithm_ranges_equal.cpp
 *
 *	@brief	ranges::equal のテスト
 */

#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/functional/ranges/greater.hpp>
#include <hamon/functional/ranges/less.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X { int i; };

struct Proj
{
	HAMON_CONSTEXPR int operator()(int t) const HAMON_NOEXCEPT
	{
		return t+1;
	}
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int x[] = { 2, 2, 6, 8, 10, 11, 11 };
	int y[] = { 2, 2, 6, 8, 10, 11, 11 };
	int z[] = { 3, 3, 7, 9, 11, 12, 12 };

	test_range<int, forward_iterator_wrapper> cx(x);
	test_range<int, forward_iterator_wrapper> cy(y);
	test_range<int, forward_iterator_wrapper> cz(z);
	VERIFY( hamon::ranges::equal(cx, cy));
	VERIFY(!hamon::ranges::equal(cx, cy, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cy, {}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cz));
	VERIFY( hamon::ranges::equal(cx, cz, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cz, {}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cy, hamon::ranges::greater{}));
	VERIFY(!hamon::ranges::equal(cx, cy, hamon::ranges::less{}));
	VERIFY( hamon::ranges::equal(cx, cy, hamon::ranges::greater{}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cy, hamon::ranges::less{},    Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cy, hamon::ranges::greater{}, {}, Proj{}));
	VERIFY( hamon::ranges::equal(cx, cy, hamon::ranges::less{},    {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cz, hamon::ranges::greater{}));
	VERIFY( hamon::ranges::equal(cx, cz, hamon::ranges::less{}));

	test_range<int, input_iterator_wrapper> rx(x);
	test_range<int, input_iterator_wrapper> ry(y);
	test_range<int, input_iterator_wrapper> rz(z);
	VERIFY( hamon::ranges::equal(rx, ry));
	VERIFY(!hamon::ranges::equal(rx, ry, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(rx, ry, {}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(rx, rz));
	VERIFY( hamon::ranges::equal(rx, rz, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(rx, rz, {}, {}, Proj{}));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int x[] = { 1, 2, 3, 4, 5 };
	int y[] = { 1, 2, 3, 4, 5 };
	int z[] = { 1, 2, 3, 4, 5, 6 };
	int w[] = { 1, 2, 3, 4 };

	VERIFY( hamon::ranges::equal(x, y));
	VERIFY(!hamon::ranges::equal(x, z));
	VERIFY(!hamon::ranges::equal(x, w));
	VERIFY(!hamon::ranges::equal(x, y, hamon::ranges::greater{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::greater{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::greater{}));
	VERIFY(!hamon::ranges::equal(x, y, hamon::ranges::less{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::less{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::less{}));
	VERIFY( hamon::ranges::equal(x, y, hamon::ranges::greater{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::greater{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::greater{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, y, hamon::ranges::less{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::less{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::less{}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, y, hamon::ranges::greater{}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::greater{}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::greater{}, {}, Proj{}));
	VERIFY( hamon::ranges::equal(x, y, hamon::ranges::less{}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, z, hamon::ranges::less{}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(x, w, hamon::ranges::less{}, {}, Proj{}));

	return true;
}

bool test03()
{
	int x[] = { 2, 2, 6, 8, 10, 11, 11 };
	int y[] = { 2, 2, 6, 8, 10, 11, 11 };
	X   z[] = { {2}, {6}, {8}, {10}, {2}, {2} };
	int w[] = { 1, 1, 1, 1, 1 };

	VERIFY(hamon::ranges::equal(w, w + 4, w + 1, w + 5));
	VERIFY(hamon::ranges::equal(w, w + 5, w, w + 5, hamon::ranges::greater{}, Proj{}));

	test_range<int, forward_iterator_wrapper> cx(x), cy(y);
	test_range<X, forward_iterator_wrapper> cz(z);
	VERIFY(hamon::ranges::equal(cx, cy));
	VERIFY(!hamon::ranges::equal(cx, cy, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(cx, cz, {}, {}, &X::i));

	test_range<int, input_iterator_wrapper> rx(x), ry(y);
	test_range<X, input_iterator_wrapper> rz(z);
	VERIFY(hamon::ranges::equal(rx, ry));

	rx.m_first = x;
	ry.m_first = y;
	VERIFY(!hamon::ranges::equal(rx, ry, {}, {}, Proj{}));

	rx.m_first = x;
	rz.m_first = z;
	VERIFY(!hamon::ranges::equal(rx, rz, {}, {}, &X::i));

	return true;
}

bool test04()
{
	X   x[] = { {2}, {2}, {6}, { 8}, {10}, {11} };
	X   y[] = { {2}, {6}, {8}, {10}, {11}, { 2} };
	int z[] = { 2, 6, 8, 10, 2, 2 };
	int w[] = { 2, 6, 8, 10, 2, 2 };

	VERIFY(hamon::ranges::equal(z, w));
	VERIFY(hamon::ranges::equal(z, w, {}));
	VERIFY(!hamon::ranges::equal(z, w, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(z, w, {}, {}, Proj{}));
	VERIFY(!hamon::ranges::equal(z, z + 5, w + 1, w + 6));
	VERIFY(!hamon::ranges::equal(z, z + 5, w + 1, w + 5));
	VERIFY(!hamon::ranges::equal(x, y, {}, &X::i, &X::i));
	VERIFY(hamon::ranges::equal(x + 1, x + 5, y, y + 4, {}, &X::i, &X::i));

	return true;
}

bool test05()
{
	std::vector<int> x = {2, 2, 6, 8, 10, 11};
	std::vector<int> y = {2, 2, 6, 8, 10, 11};
	std::vector<int> z = {2, 2, 6, 8, 10, 12};
	VERIFY( hamon::ranges::equal(x, y));
	VERIFY(!hamon::ranges::equal(x, z));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	EXPECT_TRUE(test03());
	EXPECT_TRUE(test04());
	EXPECT_TRUE(test05());
}

}	// namespace ranges_equal_test

}	// namespace hamon_algorithm_test
