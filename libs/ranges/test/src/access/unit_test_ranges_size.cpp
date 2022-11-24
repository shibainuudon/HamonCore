/**
 *	@file	unit_test_ranges_size.cpp
 *
 *	@brief	ranges::size のテスト
 */

#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/concepts/disable_sized_range.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace size_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

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

struct Incomplete;
using A = Incomplete[2]; // bounded array of incomplete type
extern A& f();

static_assert(hamon::same_as_t<decltype(hamon::ranges::size(f())), std::size_t>::value, "");

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
	constexpr int a[10] {};
	static_assert(hamon::ranges::size(a) == 10, "");
	static_assert(noexcept(hamon::ranges::size(a)), "");

	int a2[2] {};
	VERIFY(hamon::ranges::size(a2) == 2);
	static_assert(noexcept(hamon::ranges::size(a2)), "");

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	R r;
	const R& c = r;

	static_assert(!noexcept(hamon::ranges::size(r)), "");
	static_assert( noexcept(hamon::ranges::size(c)), "");

	VERIFY(hamon::ranges::size(r) == 1);
	VERIFY(hamon::ranges::size(c) == 2L);

	int a[3] { };
	test_sized_range<int, input_iterator_wrapper> ri(a);
	static_assert(noexcept(hamon::ranges::size(ri)), "");
	VERIFY(hamon::ranges::size(ri) == 3);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R3 r;
	const R3& c = r;
	
	static_assert( noexcept(hamon::ranges::size(r)), "");
	static_assert( noexcept(hamon::ranges::size(std::move(r))), "");
	static_assert(!noexcept(hamon::ranges::size(c)), "");
	static_assert(!noexcept(hamon::ranges::size(std::move(c))), "");

	VERIFY(hamon::ranges::size(r) == 1);
	VERIFY(hamon::ranges::size(std::move(r)) == 1);
	VERIFY(hamon::ranges::size(c) == 2L);
	VERIFY(hamon::ranges::size(std::move(c)) == 2L);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	int a[] { 0, 1 };
	test_range<int, random_access_iterator_wrapper> r(a);
	VERIFY(hamon::ranges::size(r) == unsigned(hamon::ranges::end(r) - hamon::ranges::begin(r)));
	
	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	R5 r;
	VERIFY(hamon::ranges::size(r) == 1);
	return true;
}

GTEST_TEST(RangesTest, SizeTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

#undef VERIFY

}	// namespace size_test

}	// namespace hamon_ranges_test
