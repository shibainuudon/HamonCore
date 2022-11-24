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
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace rbegin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

struct R3 : test_range<int, bidirectional_iterator_wrapper>
{
	HAMON_CXX14_CONSTEXPR R3(int(&a)[2]) : test_range(a) { }

	using test_range::begin;

	// Replace test_range::end() to return same type as begin()
	// so ranges::rbegin will wrap it in a reverse_iterator .
	HAMON_CXX14_CONSTEXPR bidirectional_iterator_wrapper<int>
	end() &
	{
		return bidirectional_iterator_wrapper<int>{m_last};
	}
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
	constexpr R1 r;
	// decay-copy(t.rbegin()) if it is a valid expression
	// and its type I models input_or_output_iterator.
	VERIFY(hamon::ranges::rbegin(r) == &r.i);
	VERIFY(hamon::ranges::rbegin(std::move(r)) == &r.i);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	constexpr R2 r;
	// Otherwise, decay-copy(rbegin(t)) if it is a valid expression
	// and its type I models input_or_output_iterator [...]
	VERIFY(hamon::ranges::rbegin(r) == hamon::make_reverse_iterator(hamon::ranges::end(r)));
	VERIFY(hamon::ranges::rbegin(std::move(r)) == hamon::make_reverse_iterator(hamon::ranges::end(std::move(r))));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	int a[2] {};
	R3 r(a);

	// Otherwise, make_reverse_iterator(ranges::end(t)) if both ranges::begin(t)
	// and ranges::end(t) are valid expressions of the same type I which models
	// bidirectional_iterator.

	VERIFY(hamon::ranges::rbegin(r) == hamon::make_reverse_iterator(hamon::ranges::end(r)));

	return true;
}

GTEST_TEST(RangesTest, RBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace rbegin_test

}	// namespace hamon_ranges_test
