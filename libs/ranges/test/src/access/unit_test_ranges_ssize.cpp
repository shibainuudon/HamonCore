/**
 *	@file	unit_test_ranges_ssize.cpp
 *
 *	@brief	ranges::ssize のテスト
 */

#include <hamon/ranges/ssize.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace ssize_test
{

struct R
{
	HAMON_CXX14_CONSTEXPR int size() const noexcept { return 0; }
	HAMON_CXX14_CONSTEXPR R* begin() { return this; }
	HAMON_CXX14_CONSTEXPR R* end() { return this + 1; }
};

}	// namespace ssize_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true, hamon_ranges_test::ssize_test::R);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace ssize_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[10] = {};
	int a2[2]  = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::ssize(a1)), std::ptrdiff_t>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::ssize(a2)), std::ptrdiff_t>::value, "");

	static_assert(hamon::signed_integral_t<decltype(hamon::ranges::ssize(a1))>::value, "");
	static_assert(hamon::signed_integral_t<decltype(hamon::ranges::ssize(a2))>::value, "");

#if 0//!(defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 90000))
	static_assert(noexcept(hamon::ranges::ssize(a1)), "");
	static_assert(noexcept(hamon::ranges::ssize(a2)), "");
#endif

	return
		hamon::ranges::ssize(a1) == 10 &&
		hamon::ranges::ssize(a2) == 2;
}

bool test02()
{
	std::vector<int> v = {1,2,3,4};
	static_assert(hamon::signed_integral_t<decltype(hamon::ranges::ssize(v))>::value, "");
	return hamon::ranges::size(v) == 4;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R r{};
	static_assert(hamon::signed_integral_t<decltype(hamon::ranges::ssize(r))>::value, "");
	return hamon::ranges::ssize(r) == 1;
}

GTEST_TEST(RangesTest, SSizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
}

}	// namespace ssize_test

}	// namespace hamon_ranges_test
