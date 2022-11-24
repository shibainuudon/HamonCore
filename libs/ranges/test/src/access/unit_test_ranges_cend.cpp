/**
 *	@file	unit_test_ranges_cend.cpp
 *
 *	@brief	ranges::cend のテスト
 */

#include <hamon/ranges/cend.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/as_const.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	int a[4] { 0, 1, 2, 3 };

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R&&) noexcept { return nullptr; }

	// Should be ignored because it doesn't return a sentinel for int*
	HAMON_CXX14_CONSTEXPR const long* end() const { return nullptr; }

	friend HAMON_CXX14_CONSTEXPR       int* end(R& r) { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* end(R&& r) { return r.a + 1; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const R& r) noexcept { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const R&& r) noexcept { return r.a + 3; }
};

struct RV // view on an R
{
	R& r;

	friend HAMON_CXX14_CONSTEXPR const int* begin(RV& rv) { return rv.r.begin(); }
	friend HAMON_CXX14_CONSTEXPR       int* end(RV& rv) { return end(rv.r); }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return rv.r.begin(); }
	friend HAMON_CXX14_CONSTEXPR const int* end(const RV& rv) noexcept { return end(hamon::as_const(rv.r)); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] { 0, 1, 2, 3 };

	       HAMON_CXX14_CONSTEXPR const void* begin() const; // return type not an iterator

	friend HAMON_CXX14_CONSTEXPR       int*   end(RR&) { /*HAMON_ASSERT(false);*/ return nullptr; }
	       HAMON_CXX14_CONSTEXPR       short* end() noexcept { return &s; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const RR&) noexcept { return nullptr; }
	       HAMON_CXX14_CONSTEXPR const long* end() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR       int* begin(RR&&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR       int* end(RR&& r) { return r.a + 1; }

	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const RR&& r) noexcept { return r.a + 3; }
};

}	// namespace cend_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// Allow ranges::end to work with RV&&
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cend_test::RV);

// N.B. this is a lie, begin/end on an RR rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cend_test::RR);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace cend_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cend(a)), "");
	VERIFY(hamon::ranges::cend(a) == (a + 2));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	VERIFY(hamon::ranges::cend(r) == hamon::ranges::end(c));
	VERIFY(hamon::ranges::cend(c) == hamon::ranges::end(c));

	RV v{ r };
	const RV cv{ r };
	VERIFY(hamon::ranges::cend(std::move(v)) == hamon::ranges::end(c));
	VERIFY(hamon::ranges::cend(std::move(cv)) == hamon::ranges::end(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;
	VERIFY(hamon::ranges::cend(r) == hamon::ranges::end(c));
	VERIFY(hamon::ranges::cend(c) == hamon::ranges::end(c));

	VERIFY(hamon::ranges::cend(std::move(r)) == hamon::ranges::end(c));
	VERIFY(hamon::ranges::cend(std::move(c)) == hamon::ranges::end(c));

	return true;
}

GTEST_TEST(RangesTest, CEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace cend_test

}	// namespace hamon_ranges_test
