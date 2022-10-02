/**
 *	@file	unit_test_compare_three_way_comparable.cpp
 *
 *	@brief	three_way_comparable のテスト
 */

#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_compare_test
{

namespace three_way_comparable_test
{

static_assert(hamon::three_way_comparable<int>, "");
static_assert(hamon::three_way_comparable<char>, "");
static_assert(hamon::three_way_comparable<float>, "");

struct X1
{
	int n;
	friend bool operator==(const X1& a, const X1& b) { return a.n == b.n; }
};
static_assert(!hamon::three_way_comparable<X1>, "");

struct X2
{
	int n;
	friend bool operator==(const X2& a, const X2& b) { return a.n == b.n; }
	friend bool operator< (const X2& a, const X2& b) { return a.n <  b.n; }
};
static_assert(!hamon::three_way_comparable<X2>, "");

struct X3
{
	int n;
	friend auto operator<=>(const X3& a, const X3& b) = default;
};
static_assert(hamon::three_way_comparable<X3>, "");

}	// namespace three_way_comparable_test

}	// namespace hamon_compare_test

#endif
