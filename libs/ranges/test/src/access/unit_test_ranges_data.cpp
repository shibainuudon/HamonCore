/**
 *	@file	unit_test_ranges_data.cpp
 *
 *	@brief	ranges::data のテスト
 */

#include <hamon/ranges/data.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/memory/to_address.hpp>
#include <gtest/gtest.h>
#include <utility>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace data_test
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
	friend HAMON_CXX14_CONSTEXPR long* begin(R3& r) { return &r.l; }
	friend HAMON_CXX14_CONSTEXPR const long* begin(const R3& r) { return &r.l + 1; }
};

}	// namespace data_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

// N.B. this is a lie, begin on an R3 rvalue will return a dangling pointer.
template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::data_test::R3);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace data_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	R r;
	const R& c = r;

	static_assert(!noexcept(hamon::ranges::data(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::data(std::declval<R const&>())), "");

	return
		hamon::ranges::data(r) == &r.j &&
		hamon::ranges::data(c) == (R*)nullptr;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={0, 1};
	return hamon::ranges::data(a) == a + 0;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;
	(void)c;
	// r.data() can only be used on an lvalue, but ranges::begin(R3&&) is OK
	// because R3 satisfies ranges::borrowed_range.
	return
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
		hamon::ranges::data(std::move(r)) == hamon::to_address(hamon::ranges::begin(std::move(r))) &&
		hamon::ranges::data(std::move(c)) == hamon::to_address(hamon::ranges::begin(std::move(c))) &&
#endif
		true;
}

GTEST_TEST(RangesTest, DataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace data_test

}	// namespace hamon_ranges_test
