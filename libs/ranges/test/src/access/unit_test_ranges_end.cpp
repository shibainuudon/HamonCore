/**
 *	@file	unit_test_ranges_end.cpp
 *
 *	@brief	ranges::end のテスト
 */

#include <hamon/ranges/end.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/iterator/ranges/next.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/utility/as_const.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace end_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R
{
	int a[4] { 0, 1, 2, 3 };

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
	int a[4] { 0, 1, 2, 3 };

	       HAMON_CXX14_CONSTEXPR const void* begin() const; // return type not an iterator

	friend                       const short* begin(RR&) noexcept;
	       HAMON_CXX14_CONSTEXPR short* end() noexcept { return &s; }

	friend                       const long* begin(const RR&) noexcept;
	       HAMON_CXX14_CONSTEXPR const long* end() const { return &l; }

	friend HAMON_CXX14_CONSTEXPR const int* begin(RR&&) noexcept;
	friend                       int* end(RR&) { return nullptr;/*throw 1;*/ } // not valid for rvalues
	friend HAMON_CXX14_CONSTEXPR int* end(RR&& r) { return r.a + 1; }

	friend HAMON_CXX14_CONSTEXPR const int* begin(const RR&&) noexcept;
	friend                       const int* end(const RR&) { return nullptr;/*throw 1;*/ } // not valid for rvalues
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
	VERIFY(hamon::ranges::end(a) == (a + 2));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={ 0, 1 };

	// Otherwise, decay-copy(t.end()) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::begin(E))>.

	test_random_access_range<int> r(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(r)), decltype(r.end())>::value, "");
	VERIFY(hamon::ranges::end(r) == hamon::ranges::next(r.begin(), 2));

	test_input_range<int> i(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(i)), decltype(i.end())>::value, "");
	VERIFY(hamon::ranges::end(i) == hamon::ranges::next(i.begin(), 2));

	test_output_range<int> o(a);
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(o)), decltype(o.end())>::value, "");
	VERIFY(hamon::ranges::end(o) == hamon::ranges::next(o.begin(), 2));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r;
	const R& c = r;

	// Otherwise, decay-copy(end(t)) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::begin(E))>.

	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(r)), decltype(end(r))>::value, "");
	static_assert(!noexcept(hamon::ranges::end(r)), "");
	VERIFY(hamon::ranges::end(r) == end(r));

	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(c)), decltype(end(c))>::value, "");
	static_assert(noexcept(hamon::ranges::end(c)), "");
	VERIFY(hamon::ranges::end(c) == end(c));

	RV v{ r };
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(std::move(v))), decltype(end(r))>::value, "");
	static_assert(noexcept(hamon::ranges::end(std::move(v))), "");
	VERIFY(hamon::ranges::end(std::move(v)) == end(r));

	const RV cv{ r };
	static_assert(hamon::same_as_t<decltype(hamon::ranges::end(std::move(cv))), decltype(end(c))>::value, "");
	static_assert(!noexcept(hamon::ranges::end(std::move(cv))), "");
	VERIFY(hamon::ranges::end(std::move(cv)) == end(c));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	RR r;
	const RR& c = r;
	VERIFY(hamon::ranges::end(r) == &r.s);
	static_assert(noexcept(hamon::ranges::end(r)), "");

	VERIFY(hamon::ranges::end(std::move(r)) == &r.s);
	static_assert(noexcept(hamon::ranges::end(std::move(r))), "");

	VERIFY(hamon::ranges::end(c) == &r.l);
	static_assert(!noexcept(hamon::ranges::end(c)), "");

	VERIFY(hamon::ranges::end(std::move(c)) == &r.l);
	static_assert(!noexcept(hamon::ranges::end(std::move(c))), "");

	return true;
}

GTEST_TEST(RangesTest, EndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace end_test

}	// namespace hamon_ranges_test
