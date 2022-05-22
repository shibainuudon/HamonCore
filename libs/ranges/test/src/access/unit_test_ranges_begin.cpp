/**
 *	@file	unit_test_ranges_begin.cpp
 *
 *	@brief	ranges::begin のテスト
 */

#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace begin_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

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
	int a[4] ={0, 1, 2, 3};

	       HAMON_CXX14_CONSTEXPR       short* begin() noexcept { return &s; }
	       HAMON_CXX14_CONSTEXPR const long*  begin() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR       int* begin(RR& r) noexcept { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(RR&& r); // not defined
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR& r) { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&& r) noexcept; // not defined
};

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

	static_assert(std::is_same<decltype(hamon::ranges::begin(a)), decltype(a + 0)>::value, "");
	static_assert(noexcept(hamon::ranges::begin(a)), "");
	return hamon::ranges::begin(a) == (a + 0);
}

bool test02()
{
	std::vector<int> v ={1,2,3};

	static_assert(std::is_same<decltype(hamon::ranges::begin(v)), decltype(v.begin())>::value, "");
	return hamon::ranges::begin(v) == v.begin();
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	// enable_borrowed_range<RV> allows ranges::begin to work for rvalues,
	// but it will call v.begin() or begin(v) on an lvalue:
	const RV cv{r};

	static_assert(std::is_same<decltype(hamon::ranges::begin(r)), decltype(begin(r))>::value, "");
	static_assert(std::is_same<decltype(hamon::ranges::begin(c)), decltype(begin(c))>::value, "");
	static_assert(std::is_same<decltype(hamon::ranges::begin(std::move(v))), decltype(begin(v))>::value, "");
	static_assert(std::is_same<decltype(hamon::ranges::begin(std::move(cv))), decltype(begin(cv))>::value, "");

	static_assert(!noexcept(hamon::ranges::begin(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::begin(std::declval<R const&>())), "");
	static_assert(!noexcept(hamon::ranges::begin(std::move(v))), "");
	static_assert( noexcept(hamon::ranges::begin(std::move(cv))), "");

	return
		hamon::ranges::begin(r) == begin(r) &&
		hamon::ranges::begin(c) == begin(c) &&
		hamon::ranges::begin(std::move(v))  == begin(v) &&
		hamon::ranges::begin(std::move(cv)) == begin(cv);
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

	static_assert( noexcept(hamon::ranges::begin(std::declval<RR&>())), "");
	static_assert(!noexcept(hamon::ranges::begin(std::declval<RR const&>())), "");
	static_assert( noexcept(hamon::ranges::begin(std::move(r))), "");
	static_assert(!noexcept(hamon::ranges::begin(std::move(c))), "");

	return
		hamon::ranges::begin(r) == &r.s &&
		hamon::ranges::begin(c) == &r.l &&
		hamon::ranges::begin(std::move(r)) == hamon::ranges::begin(r) &&
		hamon::ranges::begin(std::move(c)) == hamon::ranges::begin(c);
}

GTEST_TEST(RangesTest, BeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace begin_test

}	// namespace hamon_ranges_test
