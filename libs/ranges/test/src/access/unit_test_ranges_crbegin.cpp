/**
 *	@file	unit_test_ranges_crbegin.cpp
 *
 *	@brief	ranges::crbegin のテスト
 */

#include <hamon/ranges/crbegin.hpp>
#include <hamon/ranges/rbegin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace crbegin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int i = 0;
	int j = 0;

	       HAMON_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	friend HAMON_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }

	HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	HAMON_CXX14_CONSTEXPR const int* end() const { return nullptr; }
};

struct R1V // view on an R1
{
	R1& r;

	friend HAMON_CXX14_CONSTEXPR const long* rbegin(R1V&); // this is not defined
	friend HAMON_CXX14_CONSTEXPR const int* rbegin(const R1V& rv) noexcept { return rv.r.rbegin(); }

	HAMON_CXX14_CONSTEXPR const int* begin() const;
	HAMON_CXX14_CONSTEXPR const int* end() const;
};

struct R2
{
	int a[2] ={};
	long l[2] ={};

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return a; }
	       HAMON_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const R2&&); // not defined
	friend HAMON_CXX14_CONSTEXPR const long* end(const R2&&); // not defined
};

}	// namespace crbegin_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// Allow ranges::end to work with R1V&&
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::crbegin_test::R1V);

// N.B. this is a lie, rbegin on an R2 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::crbegin_test::R2);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace crbegin_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	const R1& c = r;
	VERIFY(hamon::ranges::crbegin(r) == hamon::ranges::rbegin(c));
	VERIFY(hamon::ranges::crbegin(c) == hamon::ranges::rbegin(c));

	//R1V v{ r };
	//const R1V cv{ r };
	//VERIFY(hamon::ranges::crbegin(hamon::move(v))  == hamon::ranges::rbegin(c));
	//VERIFY(hamon::ranges::crbegin(hamon::move(cv)) == hamon::ranges::rbegin(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	const R2& c = r;
	VERIFY(hamon::ranges::crbegin(r) == hamon::ranges::rbegin(c));
	VERIFY(hamon::ranges::crbegin(c) == hamon::ranges::rbegin(c));

	VERIFY(hamon::ranges::crbegin(hamon::move(r)) == hamon::ranges::rbegin(c));
	VERIFY(hamon::ranges::crbegin(hamon::move(c)) == hamon::ranges::rbegin(c));

	return true;
}

GTEST_TEST(RangesTest, CRBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

#undef VERIFY

}	// namespace crbegin_test

}	// namespace hamon_ranges_test
