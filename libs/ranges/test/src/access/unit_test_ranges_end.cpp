/**
 *	@file	unit_test_ranges_end.cpp
 *
 *	@brief	ranges::end のテスト
 */

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

namespace end_test
{

struct R
{
	int a[4] ={0, 1, 2, 3};

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR       int* begin(R&&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* begin(const R&&) noexcept { return nullptr; }

	// Should be ignored because it doesn't return a sentinel for int*
	       HAMON_CXX14_CONSTEXPR const long* end() const;

	friend HAMON_CXX14_CONSTEXPR       int* end(R& r) { return r.a + 0; }
	friend HAMON_CXX14_CONSTEXPR       int* end(R&& r) { return r.a + 1; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const R& r) noexcept { return r.a + 2; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const R&& r) noexcept { return r.a + 3; }
};

struct RV // view on an R
{
	R& r;

	       HAMON_CXX14_CONSTEXPR const int* begin() const { return nullptr; }

	friend HAMON_CXX14_CONSTEXPR       int* end(RV& v) noexcept { return end(v.r); }
	friend HAMON_CXX14_CONSTEXPR const int* end(const RV& v) { return end(hamon::as_const(v.r)); }
};

struct RR
{
	short s = 0;
	long l = 0;
	int a[4] ={0, 1, 2, 3};

	       HAMON_CXX14_CONSTEXPR const void* begin() const { return nullptr; } // return type not an iterator

	friend HAMON_CXX14_CONSTEXPR const short* begin(RR&) noexcept { return nullptr; }
	       HAMON_CXX14_CONSTEXPR       short* end() noexcept { return &s; }

	friend HAMON_CXX14_CONSTEXPR const long* begin(const RR&) noexcept { return nullptr; }
	       HAMON_CXX14_CONSTEXPR const long* end() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR const int* begin(RR&&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR       int* end(RR&) { /*assert(false);*/ return nullptr; } // not valid for rvalues
	friend HAMON_CXX14_CONSTEXPR       int* end(RR&& r) { return r.a + 1; }

	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&&) noexcept { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR const int* end(const RR&) { /*assert(false);*/ return nullptr; } // not valid for rvalues
	friend HAMON_CXX14_CONSTEXPR const int* end(const RR&& r) noexcept { return r.a + 3; }
};

}	// namespace end_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// Allow ranges::begin to work with RV&&
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::end_test::RV);

// N.B. this is a lie, end on an RR rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::end_test::RR);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace end_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};

	// t + extent_v<T> if E is of array type T.

	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(a)), decltype(a + 2)>::value, "");
	static_assert(noexcept(hamon::ranges::end(a)), "");
	return hamon::ranges::end(a) == (a + 2);
}

bool test02()
{
	std::vector<int> v ={1,2,3};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(v)), decltype(v.end())>::value, "");
	return hamon::ranges::end(v) == v.end();
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;
	RV v{r};
	const RV cv{r};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(r)), decltype(end(r))>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(c)), decltype(end(c))>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(std::move(v))), decltype(end(r))>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(std::move(cv))), decltype(end(c))>::value, "");

	static_assert(!noexcept(hamon::ranges::end(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::end(std::declval<R const&>())), "");
	static_assert( noexcept(hamon::ranges::end(std::move(v))), "");
	static_assert(!noexcept(hamon::ranges::end(std::move(cv))), "");

	return
		hamon::ranges::end(r) == end(r) &&
		hamon::ranges::end(c) == end(c) &&
		hamon::ranges::end(std::move(v)) == end(r) &&
		hamon::ranges::end(std::move(cv)) == end(c);
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;

	static_assert( noexcept(hamon::ranges::end(std::declval<RR&>())), "");
	static_assert(!noexcept(hamon::ranges::end(std::declval<RR const&>())), "");
	static_assert( noexcept(hamon::ranges::end(std::move(r))), "");
	static_assert(!noexcept(hamon::ranges::end(std::move(c))), "");

	return
		hamon::ranges::end(r) == &r.s &&
		hamon::ranges::end(c) == &r.l &&
		hamon::ranges::end(std::move(r)) == &r.s &&
		hamon::ranges::end(std::move(c)) == &r.l;
}

GTEST_TEST(RangesTest, EndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace end_test

}	// namespace hamon_ranges_test
