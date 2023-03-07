/**
 *	@file	unit_test_ranges_cdata.cpp
 *
 *	@brief	ranges::cdata のテスト
 */

#include <hamon/ranges/cdata.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cdata_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
using has_cdata_t = decltype(hamon::ranges::cdata(hamon::declval<T&&>()));

template <typename T>
using has_cdata = hamon::is_detected<has_cdata_t, T>;

struct R
{
	int i = 0;
	int j = 0;
	HAMON_CXX14_CONSTEXPR int* data() { return &j; }
	HAMON_CXX14_CONSTEXPR const R* data() const noexcept { return nullptr; }
};

struct R3
{
	static int i;
	static long l;

	HAMON_CXX14_CONSTEXPR int* data() &; // this function is not defined
	friend HAMON_CXX14_CONSTEXPR long* begin(R3&& r); // not defined
	friend HAMON_CXX14_CONSTEXPR const long* begin(const R3& r) { return &r.l; }
	friend HAMON_CXX14_CONSTEXPR const short* begin(const R3&&); // not defined
};

int R3::i = 0;
long R3::l = 0;

}	// namespace cdata_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon_ranges_test::cdata_test::R3);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace cdata_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	static_assert(has_cdata<R&>::value, "");
	static_assert(has_cdata<const R&>::value, "");
	R r;
	const R& c = r;
	VERIFY(hamon::ranges::cdata(r) == (R*)nullptr);
	static_assert(noexcept(hamon::ranges::cdata(r)), "");
	VERIFY(hamon::ranges::cdata(c) == (R*)nullptr);
	static_assert(noexcept(hamon::ranges::cdata(c)), "");

	// not lvalues and not borrowed ranges
	static_assert(!has_cdata<R>::value, "");
	static_assert(!has_cdata<const R>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={ 0, 1 };
	VERIFY(hamon::ranges::cdata(a) == a + 0);

	static_assert( has_cdata<int(&)[2]>::value, "");
	static_assert(!has_cdata<int(&&)[2]>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	static_assert(has_cdata<R3&>::value, "");
	static_assert(has_cdata<R3>::value, "");  // borrowed range
	static_assert(has_cdata<const R3&>::value, "");
	static_assert(has_cdata<const R3>::value, "");  // borrowed range

	R3 r;
	const R3& c = r;
	VERIFY(hamon::ranges::cdata(r) == hamon::ranges::data(c));
	VERIFY(hamon::ranges::cdata(hamon::move(r)) == hamon::ranges::data(c));
	VERIFY(hamon::ranges::cdata(hamon::move(c)) == hamon::ranges::begin(c));

	return true;
}

GTEST_TEST(RangesTest, CDataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace cdata_test

}	// namespace hamon_ranges_test
