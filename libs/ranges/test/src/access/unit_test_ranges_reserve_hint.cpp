/**
 *	@file	unit_test_ranges_reserve_hint.cpp
 *
 *	@brief	ranges::reserve_hint のテスト
 */

#include <hamon/ranges/reserve_hint.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace reserve_hint_test
{

struct R1
{
	HAMON_CXX14_CONSTEXPR hamon::size_t size() const { return 1; }
	HAMON_CXX14_CONSTEXPR int reserve_hint() const { return 2; }
	friend HAMON_CXX14_CONSTEXPR long reserve_hint(R1 const&) { return 3; }
};

struct R2
{
//	HAMON_CXX14_CONSTEXPR hamon::size_t size() const { return 1; }
	HAMON_CXX14_CONSTEXPR int reserve_hint() const { return 2; }
	friend HAMON_CXX14_CONSTEXPR long reserve_hint(R2 const&) { return 3; }
};

struct R3
{
//	HAMON_CXX14_CONSTEXPR hamon::size_t size() const { return 1; }
//	HAMON_CXX14_CONSTEXPR int reserve_hint() const { return 2; }
	friend HAMON_CXX14_CONSTEXPR long reserve_hint(R3 const&) { return 3; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[] = {10, 20};
	static_assert(hamon::same_as_t<decltype(hamon::ranges::reserve_hint(a)), decltype(hamon::ranges::size(a))>::value, "");
	VERIFY(hamon::ranges::reserve_hint(a) == 2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R1 r;
	static_assert(hamon::same_as_t<decltype(hamon::ranges::reserve_hint(r)), hamon::size_t>::value, "");
	VERIFY(hamon::ranges::reserve_hint(r) == 1);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R2 r;
	static_assert(hamon::same_as_t<decltype(hamon::ranges::reserve_hint(r)), int>::value, "");
	VERIFY(hamon::ranges::reserve_hint(r) == 2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R3 r;
	static_assert(hamon::same_as_t<decltype(hamon::ranges::reserve_hint(r)), long>::value, "");
	VERIFY(hamon::ranges::reserve_hint(r) == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ReserveHintTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace begin_test

}	// namespace hamon_ranges_test
