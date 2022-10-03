/**
 *	@file	unit_test_ranges_size.cpp
 *
 *	@brief	ranges::size のテスト
 */

#include <hamon/ranges/size.hpp>
#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace size_test
{

struct R
{
	HAMON_CXX14_CONSTEXPR int size() { return 1; }
	HAMON_CXX14_CONSTEXPR long size() const noexcept { return 2; }
};

struct R3
{
	HAMON_CXX14_CONSTEXPR int* size() { return nullptr; }
	friend HAMON_CXX14_CONSTEXPR int size(R3&) noexcept { return 1; }
	friend HAMON_CXX14_CONSTEXPR long size(const R3&) { return 2L; }
	friend HAMON_CXX14_CONSTEXPR unsigned int size(R3&&) { return 3U; }
	friend HAMON_CXX14_CONSTEXPR unsigned long size(const R3&&) noexcept { return 4UL; }
};

struct R5
{
	HAMON_CXX14_CONSTEXPR int size() const noexcept { return 0; }
	HAMON_CXX14_CONSTEXPR R5* begin() { return this; }
	HAMON_CXX14_CONSTEXPR R5* end() { return this + 1; }
};

}	// namespace size_test

}	// namespace hamon_ranges_test

HAMON_RANGES_START_NAMESPACE

template <>
HAMON_RANGES_SPECIALIZE_DISABLE_SIZED_RANGE(true, hamon_ranges_test::size_test::R5);

HAMON_RANGES_END_NAMESPACE

namespace hamon_ranges_test
{

namespace size_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a1[10] = {};
	int a2[2]  = {};

	static_assert(noexcept(hamon::ranges::size(a1)), "");
	static_assert(noexcept(hamon::ranges::size(a2)), "");

	return
		hamon::ranges::size(a1) == 10 &&
		hamon::ranges::size(a2) == 2;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R r{};
	const R& c = r;

	static_assert(!noexcept(hamon::ranges::size(std::declval<R&>())), "");
	static_assert( noexcept(hamon::ranges::size(std::declval<R const&>())), "");

	return
		hamon::ranges::size(r) == 1 &&
		hamon::ranges::size(c) == 2L;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r{};
	const R3& c = r;

	static_assert( noexcept(hamon::ranges::size(std::declval<R3&>())), "");
	static_assert(!noexcept(hamon::ranges::size(std::declval<R3 const&>())), "");
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
	static_assert(!noexcept(hamon::ranges::size(std::declval<R3&&>())), "");
	static_assert( noexcept(hamon::ranges::size(std::declval<R3 const&&>())), "");
#endif

	return
		hamon::ranges::size(r) == 1 &&
		hamon::ranges::size(c) == 2L &&
#if !(defined(HAMON_STDLIB_DINKUMWARE) && defined(HAMON_USE_STD_RANGES))
		hamon::ranges::size(std::move(r)) == 3U &&
		hamon::ranges::size(std::move(c)) == 4UL &&
#endif
		true;
}

bool test04()
{
	std::vector<int> v = {1,2,3};

	return hamon::ranges::size(v) == 3;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	R5 r{};
	return hamon::ranges::size(r) == 1;
}

GTEST_TEST(RangesTest, SizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	                      EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace size_test

}	// namespace hamon_ranges_test
