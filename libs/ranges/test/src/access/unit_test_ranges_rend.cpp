/**
 *	@file	unit_test_ranges_rend.cpp
 *
 *	@brief	ranges::rend のテスト
 */

#include <hamon/ranges/rend.hpp>
#include <hamon/ranges/rbegin.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace rend_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       HAMON_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	       HAMON_CXX14_CONSTEXPR const int* rend() const { return &i + 1; }
	friend HAMON_CXX14_CONSTEXPR const int* rbegin(const R1&&); // not defined
	friend HAMON_CXX14_CONSTEXPR const int* rend(const R1&&); // not defined
};

struct R2
{
	int i = 0;

	       HAMON_CXX14_CONSTEXPR int* rbegin() noexcept { return &i + 1; }
	       HAMON_CXX14_CONSTEXPR long* rend() noexcept { return nullptr; } // not a sentinel for rbegin()

	friend HAMON_CXX14_CONSTEXPR long* rbegin(R2&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR int* rend(R2& r) { return &r.i; }
};

struct R3
{
	int a[2] ={};
	long l[2] ={};

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return a; }
	       HAMON_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const R3&& r) { return r.l; }
	friend HAMON_CXX14_CONSTEXPR const long* end(const R3&& r) { return r.l + 2; }
};

}	// namespace rend_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// N.B. this is a lie, rend on an R1 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::rend_test::R1);

// N.B. this is a lie, begin/end on an R3 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::rend_test::R3);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace rend_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R1 r;

	// decay-copy(t.rend()) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	return
		hamon::ranges::rend(r) == &r.i + 1 &&
		hamon::ranges::rend(std::move(r)) == &r.i + 1;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R2 r;

	// Otherwise, decay-copy(rend(t)) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	auto i1 = hamon::ranges::rbegin(r);
	auto i2 = rend(r);
	static_assert(hamon::sentinel_for_t<decltype(i2), decltype(i1)>::value, "");

	static_assert(!noexcept(hamon::ranges::rend(std::declval<R2&>())), "");

	return hamon::ranges::rend(r) == &r.i;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r;

	// Otherwise, make_reverse_iterator(ranges::begin(t)) if both
	// ranges::begin(t) and ranges::end(t) are valid expressions
	// of the same type I which models bidirectional_iterator.

	return
		hamon::ranges::rend(r)            == hamon::make_reverse_iterator(hamon::ranges::begin(r)) &&
		hamon::ranges::rend(std::move(r)) == hamon::make_reverse_iterator(hamon::ranges::begin(std::move(r)));
}

GTEST_TEST(RangesTest, REndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace rend_test

}	// namespace hamon_ranges_test
