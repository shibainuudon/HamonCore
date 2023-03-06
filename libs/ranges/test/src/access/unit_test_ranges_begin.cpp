/**
 *	@file	unit_test_ranges_begin.cpp
 *
 *	@brief	ranges::begin のテスト
 */

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace begin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	int a[4] { 0, 1, 2, 3 };

	friend HAMON_CXX14_CONSTEXPR       int* begin(R& r) { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(R&& r); // this overload is not defined
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R& r) noexcept { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R&& r) noexcept; // not defined
};

struct RV // view on an R
{
	R& r;

	friend HAMON_CXX14_CONSTEXPR       int* begin(RV& rv) { return begin(rv.r); }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RV& rv) noexcept { return begin(rv.r); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR       short* begin() noexcept { return &s; }
	HAMON_CXX14_CONSTEXPR const long*  begin() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR       int* begin(RR& r) noexcept { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(RR&& r); // not defined
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR& r) { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&& r) noexcept; // not defined
};

struct X { };
using A = X[]; // unbounded array
extern A& f();
static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(f())), X*>::value, "");

}	// namespace begin_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// Allow ranges::begin to work with RV&&
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::begin_test::RV);

// N.B. this is a lie, begin on an RR rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::begin_test::RR);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace begin_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(a)), decltype(a + 0)>::value, "");
	static_assert(noexcept(hamon::ranges::begin(a)), "");
	VERIFY(hamon::ranges::begin(a) == (a + 0));

	constexpr long b[2] ={ };
	static_assert(hamon::ranges::begin(b) == (b + 0), "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={ 0, 1 };

	test_random_access_range<int> r(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(r)), decltype(r.begin())>::value, "");
	VERIFY(hamon::ranges::begin(r) == r.begin());

	test_input_range<int> i(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(i)), decltype(i.begin())>::value, "");
	VERIFY(hamon::ranges::begin(i) == i.begin());

	test_output_range<int> o(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(o)), decltype(o.begin())>::value, "");
	*hamon::ranges::begin(o) = 99;
	VERIFY(a[0] == 99);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(r)), decltype(begin(r))>::value, "");
	static_assert(!noexcept(hamon::ranges::begin(r)), "");
	VERIFY(hamon::ranges::begin(r) == begin(r));

	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(c)), decltype(begin(c))>::value, "");
	static_assert(noexcept(hamon::ranges::begin(c)), "");
	VERIFY(hamon::ranges::begin(c) == begin(c));

	RV v{ r };
	// enable_borrowed_range<RV> allows ranges::begin to work for rvalues,
	// but it will call v.begin() or begin(v) on an lvalue:
	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(hamon::move(v))), decltype(begin(v))>::value, "");
	static_assert(!noexcept(hamon::ranges::begin(hamon::move(v))), "");
	VERIFY(hamon::ranges::begin(hamon::move(v)) == begin(v));

	const RV cv{ r };
	static_assert(hamon::same_as_t<decltype(hamon::ranges::begin(hamon::move(cv))), decltype(begin(cv))>::value, "");
	static_assert(noexcept(hamon::ranges::begin(hamon::move(cv))), "");
	VERIFY(hamon::ranges::begin(hamon::move(cv)) == begin(cv));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;
	VERIFY(hamon::ranges::begin(r) == &r.s);
	static_assert(noexcept(hamon::ranges::begin(r)), "");

	// calls r.begin() on an lvalue, not rvalue
	VERIFY(hamon::ranges::begin(hamon::move(r)) == hamon::ranges::begin(r));
	static_assert(noexcept(hamon::ranges::begin(hamon::move(r))), "");

	VERIFY(hamon::ranges::begin(c) == &r.l);
	static_assert(!noexcept(hamon::ranges::begin(c)), "");

	// calls r.begin() on a const lvalue, not rvalue
	VERIFY(hamon::ranges::begin(hamon::move(c)) == hamon::ranges::begin(c));
	static_assert(!noexcept(hamon::ranges::begin(hamon::move(c))), "");

	return true;
}

GTEST_TEST(RangesTest, BeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace begin_test

}	// namespace hamon_ranges_test
