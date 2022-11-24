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
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace rend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

struct R4
	: test_range<int, bidirectional_iterator_wrapper>
{
	HAMON_CXX14_CONSTEXPR R4(int(&a)[2]) : test_range(a) { }

	using test_range::begin;

	// Replace test_range::end() to return same type as begin()
	// so ranges::rend will wrap it in a reverse_iterator.
	HAMON_CXX14_CONSTEXPR bidirectional_iterator_wrapper<int>
	end() &
	{
		return bidirectional_iterator_wrapper<int>{m_last};
	}
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
	constexpr R1 r;

	// decay-copy(t.rend()) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	VERIFY(hamon::ranges::rend(r) == &r.i + 1);
	VERIFY(hamon::ranges::rend(std::move(r)) == &r.i + 1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R2 r;

	// Otherwise, decay-copy(rend(t)) if it is a valid expression
	// and its type S models sentinel_for<decltype(ranges::rbegin(E))>

	auto i1 = hamon::ranges::rbegin(r);
	auto i2 = rend(r);
	static_assert(hamon::sentinel_for_t<decltype(i2), decltype(i1)>::value, "");
	VERIFY(hamon::ranges::rend(r) == &r.i);
	static_assert(!noexcept(hamon::ranges::rend(r)), "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	constexpr R3 r;

	// Otherwise, make_reverse_iterator(ranges::begin(t)) if both
	// ranges::begin(t) and ranges::end(t) are valid expressions
	// of the same type I which models bidirectional_iterator.

	VERIFY(hamon::ranges::rend(r) == hamon::make_reverse_iterator(hamon::ranges::begin(r)));
	VERIFY(hamon::ranges::rend(std::move(r)) == hamon::make_reverse_iterator(hamon::ranges::begin(std::move(r))));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[2] ={ };
	R4 r(a);
	VERIFY(hamon::ranges::rend(r) == hamon::make_reverse_iterator(hamon::ranges::begin(r)));

	return true;
}

GTEST_TEST(RangesTest, REndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace rend_test

}	// namespace hamon_ranges_test
