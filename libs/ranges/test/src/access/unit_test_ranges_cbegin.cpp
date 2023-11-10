/**
 *	@file	unit_test_ranges_cbegin.cpp
 *
 *	@brief	ranges::cbegin のテスト
 */

#include <hamon/ranges/cbegin.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cbegin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	int a[4] ={ 0, 1, 2, 3 };

	friend HAMON_CXX14_CONSTEXPR       int* begin(R& r) { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(R&&); // this function is not defined
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R& r) noexcept { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R&&); // this function is not defined

	friend HAMON_CXX14_CONSTEXPR const int* end(const R&) noexcept { return nullptr; }
};

struct RV // view on an R
{
	R& r;

	friend HAMON_CXX14_CONSTEXPR       int* begin(RV&) { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return begin(hamon::as_const(rv.r)); }

	friend HAMON_CXX14_CONSTEXPR const int* end(const RV&) noexcept { return nullptr; }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={ 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR       short* begin() noexcept { return &s; }
	HAMON_CXX14_CONSTEXPR const long*  begin() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR       int* begin(RR& r) { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(RR&& r) { return r.a + 1; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR& r) { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&& r) noexcept { return r.a + 3; }

	HAMON_CXX14_CONSTEXPR short* end() noexcept { return &s + 1; }   // C++23 requires this.
	HAMON_CXX14_CONSTEXPR const long* end() const { return &l + 1; } // C++23 requires this.
};

}	// namespace cbegin_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// Allow ranges::begin to work with RV&&
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cbegin_test::RV);

// N.B. this is a lie, cbegin on an RR rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cbegin_test::RR);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace cbegin_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cbegin(a)), "");
	VERIFY(hamon::ranges::cbegin(a) == (a + 0));

	constexpr long b[2] ={};
	static_assert(hamon::ranges::cbegin(b) == (b + 0), "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	VERIFY(hamon::ranges::cbegin(r) == hamon::ranges::begin(c));
	VERIFY(hamon::ranges::cbegin(c) == hamon::ranges::begin(c));

	RV v{ r };
	VERIFY(hamon::ranges::cbegin(hamon::move(v)) == hamon::ranges::begin(c));
	const RV cv{ r };
	VERIFY(hamon::ranges::cbegin(hamon::move(cv)) == hamon::ranges::begin(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;
	VERIFY(hamon::ranges::cbegin(r) == hamon::ranges::begin(c));
	VERIFY(hamon::ranges::cbegin(hamon::move(r)) == hamon::ranges::begin(c));
	VERIFY(hamon::ranges::cbegin(c) == hamon::ranges::begin(c));
	VERIFY(hamon::ranges::cbegin(hamon::move(c)) == hamon::ranges::begin(c));

	return true;
}

GTEST_TEST(RangesTest, CBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace cbegin_test

}	// namespace hamon_ranges_test
