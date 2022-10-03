/**
 *	@file	unit_test_ranges_rbegin.cpp
 *
 *	@brief	ranges::rbegin のテスト
 */

#include <hamon/ranges/rbegin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace rbegin_test
{

struct R1
{
	int i = 0;
	int j = 0;

	       HAMON_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	friend HAMON_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }
};

struct R2
{
	int a[2] ={};

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return a; }
	       HAMON_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const R2&&); // not defined
	friend HAMON_CXX14_CONSTEXPR const long* end(const R2&&); // not defined
};

}	// namespace rbegin_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// N.B. this is a lie, rbegin on an R1 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::rbegin_test::R1);

// N.B. this is a lie, begin/end on an R2 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::rbegin_test::R2);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace rbegin_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	// decay-copy(t.rbegin()) if it is a valid expression
	// and its type I models input_or_output_iterator.
	return
		hamon::ranges::rbegin(r) == &r.i &&
		hamon::ranges::rbegin(std::move(r)) == &r.i;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	// Otherwise, decay-copy(rbegin(t)) if it is a valid expression
	// and its type I models input_or_output_iterator [...]
	return
		hamon::ranges::rbegin(r)            == hamon::make_reverse_iterator(hamon::ranges::end(r)) &&
		hamon::ranges::rbegin(std::move(r)) == hamon::make_reverse_iterator(hamon::ranges::end(std::move(r)));
}

GTEST_TEST(RangesTest, RBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace rbegin_test

}	// namespace hamon_ranges_test
