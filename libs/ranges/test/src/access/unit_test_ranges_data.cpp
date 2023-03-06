/**
 *	@file	unit_test_ranges_data.cpp
 *
 *	@brief	ranges::data のテスト
 */

#include <hamon/ranges/data.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace data_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
using has_data_t = decltype(hamon::ranges::data(std::declval<T>()));

template <typename T>
using has_data = hamon::is_detected<has_data_t, T>;

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

	HAMON_CXX14_CONSTEXPR int* data() & { return &i; }
	friend HAMON_CXX14_CONSTEXPR long* begin(const R3&) { return &l; }
	friend HAMON_CXX14_CONSTEXPR const short* begin(const R3&&); // not defined
};

int R3::i = 0;
long R3::l = 0;

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
	static_assert(has_data<R&>::value, "");
	static_assert(has_data<const R&>::value, "");

	R r;
	const R& c = r;
	static_assert(!noexcept(hamon::ranges::data(r)), "");
	static_assert( noexcept(hamon::ranges::data(c)), "");
	VERIFY(hamon::ranges::data(r) == &r.j);
	VERIFY(hamon::ranges::data(c) == (R*)nullptr);

	// not lvalues and not borrowed ranges
	static_assert(!has_data<R>::value, "");
	static_assert(!has_data<const R>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[] ={ 0, 1 };
	VERIFY(hamon::ranges::data(a) == a + 0);

	test_contiguous_range<int> r(a);
	VERIFY(hamon::ranges::data(r) == hamon::to_address(hamon::ranges::begin(r)));

	static_assert( has_data<int(&)[2]>::value, "");
	static_assert( has_data<decltype(r)&>::value, "");
	static_assert(!has_data<int(&&)[2]>::value, "");
	static_assert(!has_data<decltype(r)&&>::value, "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	static_assert(has_data<R3&>::value, "");
	static_assert(has_data<R3>::value, "");  // borrowed range
	static_assert(has_data<const R3&>::value, "");
	static_assert(has_data<const R3>::value, "");  // borrowed range

	R3 r;
	const R3& c = r;

	VERIFY(hamon::ranges::data(hamon::move(r)) == &R3::i);
	VERIFY(hamon::ranges::data(hamon::move(c)) == &R3::l);

	struct A { int*&& data(); };
	static_assert(has_data<A&>::value, "");

	return true;
}

GTEST_TEST(RangesTest, DataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

#undef VERIFY

}	// namespace data_test

}	// namespace hamon_ranges_test
