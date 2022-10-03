/**
 *	@file	unit_test_ranges_cdata.cpp
 *
 *	@brief	ranges::cdata のテスト
 */

#include <hamon/ranges/cdata.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cdata_test
{

struct R
{
	int i = 0;
	int j = 0;
	HAMON_CXX14_CONSTEXPR int* data() { return &j; }
	HAMON_CXX14_CONSTEXPR const R* data() const noexcept { return nullptr; }
};

struct R3
{
	long l = 0;

	HAMON_CXX14_CONSTEXPR int* data() const { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR long* begin(R3&& r); // this function is not defined
	friend HAMON_CXX14_CONSTEXPR const long* begin(const R3& r) { return &r.l; }
	friend HAMON_CXX14_CONSTEXPR const short* begin(const R3&&); // not defined
};

}	// namespace cdata_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// This is a lie, ranges::begin(R3&&) returns a dangling iterator.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cdata_test::R3);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace cdata_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R r;
	const R& c = r;

	static_assert(!noexcept(hamon::ranges::data(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::data(std::declval<R const&>())), "");
	static_assert( noexcept(hamon::ranges::cdata(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::cdata(std::declval<R const&>())), "");

	return
		hamon::ranges::data(r) == &r.j &&
		hamon::ranges::data(c) == (R*)nullptr &&
		hamon::ranges::cdata(r) == (R*)nullptr &&
		hamon::ranges::cdata(c) == (R*)nullptr;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={0, 1};
	return hamon::ranges::cdata(a) == a + 0;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;

	return
		hamon::ranges::cdata(r) == hamon::ranges::data(c) &&
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
		hamon::ranges::cdata(std::move(r)) == hamon::ranges::begin(c) &&
		hamon::ranges::cdata(std::move(c)) == hamon::ranges::begin(c) &&
#endif
		true;
}

GTEST_TEST(RangesTest, CDataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace cdata_test

}	// namespace hamon_ranges_test
