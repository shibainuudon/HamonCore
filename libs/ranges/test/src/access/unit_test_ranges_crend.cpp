/**
 *	@file	unit_test_ranges_crend.cpp
 *
 *	@brief	ranges::crend のテスト
 */

#include <hamon/ranges/crend.hpp>
#include <hamon/ranges/rend.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace crend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int i = 0;
	int j = 0;

	       HAMON_CXX14_CONSTEXPR const int* rbegin() const { return &i; }
	       HAMON_CXX14_CONSTEXPR const int* rend() const { return &i + 1; }
	friend HAMON_CXX14_CONSTEXPR const int* rbegin(const R1&& r) { return &r.j; }
	friend HAMON_CXX14_CONSTEXPR const int* rend(const R1&& r) { return &r.j + 1; }

	HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	HAMON_CXX14_CONSTEXPR const int* end() const { return nullptr; }
};

struct R2
{
	int a[2] ={};
	long l[2] ={};

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return a; }
	       HAMON_CXX14_CONSTEXPR const int* end() const { return a + 2; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const R2&& r) { return r.l; }
	friend HAMON_CXX14_CONSTEXPR const long* end(const R2&& r) { return r.l + 2; }
};

struct R3
{
	int i = 0;

	       HAMON_CXX14_CONSTEXPR const int* rbegin() const noexcept { return &i + 1; }
	       HAMON_CXX14_CONSTEXPR const long* rend() const noexcept { return nullptr; } // not a sentinel for rbegin()

	friend HAMON_CXX14_CONSTEXPR const long* rbegin(const R3&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* rend(const R3& r) { return &r.i; }

	HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	HAMON_CXX14_CONSTEXPR const int* end() const { return nullptr; }
};

}	// namespace crend_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// N.B. this is a lie, rend on an R1 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::crend_test::R1);

// N.B. this is a lie, rend on an R2 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::crend_test::R2);

// N.B. this is a lie, rend on an R3 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::crend_test::R3);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace crend_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R1 r;
	const R1& c = r;
	VERIFY(hamon::ranges::crend(r) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(c) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(hamon::move(r)) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(hamon::move(c)) == hamon::ranges::rend(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R2 r;
	const R2& c = r;
	VERIFY(hamon::ranges::crend(r) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(c) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(hamon::move(r)) == hamon::ranges::rend(hamon::move(c)));
	VERIFY(hamon::ranges::crend(hamon::move(c)) == hamon::ranges::rend(hamon::move(c)));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;
	static_assert(!noexcept(hamon::ranges::crend(r)), "");
	static_assert(!noexcept(hamon::ranges::crend(c)), "");
	VERIFY(hamon::ranges::crend(r) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(c) == hamon::ranges::rend(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={ };
	const auto& c = a;
	VERIFY(hamon::ranges::crend(a) == hamon::ranges::rend(c));
	VERIFY(hamon::ranges::crend(c) == hamon::ranges::rend(c));

	return true;
}

GTEST_TEST(RangesTest, CREndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace crend_test

}	// namespace hamon_ranges_test
