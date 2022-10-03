/**
 *	@file	unit_test_ranges_empty.cpp
 *
 *	@brief	ranges::empty のテスト
 */

#include <hamon/ranges/empty.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{

namespace empty_test
{

HAMON_CXX14_CONSTEXPR bool test01()
{
	int a[2] ={};
	return !hamon::ranges::empty(a);
}

bool test02()
{
	std::vector<int> v1 ={1};
	std::vector<int> v2;
	std::list<int>   l1 ={1,2};
	std::list<int>   l2;
	std::forward_list<int> fl1 ={1,2,3};
	std::forward_list<int> fl2;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(v1)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(v2)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(l1)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(l2)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(fl1)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(fl2)), bool>::value, "");

	return
		!hamon::ranges::empty(v1) &&
		 hamon::ranges::empty(v2) &&
		!hamon::ranges::empty(l1) &&
		 hamon::ranges::empty(l2) &&
		!hamon::ranges::empty(fl1) &&
		 hamon::ranges::empty(fl2);
}

struct R1
{
	HAMON_CXX14_CONSTEXPR int empty() const noexcept { return 0; }
};
struct R2
{
	HAMON_CXX14_CONSTEXPR const void* empty() const { return this; }
};

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r1{};
	R2 r2{};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r1)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r2)), bool>::value, "");

	static_assert( noexcept(hamon::ranges::empty(std::declval<R1 const&>())), "");
	static_assert(!noexcept(hamon::ranges::empty(std::declval<R2 const&>())), "");

	return
		!hamon::ranges::empty(r1) &&
		 hamon::ranges::empty(r2);
}

struct R3
{
	HAMON_CXX14_CONSTEXPR int size() const noexcept { return 0; }
};
struct R4
{
	HAMON_CXX14_CONSTEXPR int size() const { return 1; }
};

HAMON_CXX14_CONSTEXPR bool test04()
{
	R3 r3{};
	R4 r4{};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r3)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r4)), bool>::value, "");

	static_assert( noexcept(hamon::ranges::empty(std::declval<R3 const&>())), "");
	static_assert(!noexcept(hamon::ranges::empty(std::declval<R4 const&>())), "");

	return
		 hamon::ranges::empty(r3) &&
		!hamon::ranges::empty(r4);
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	int a[2] {};
	test_forward_range<int>       r1{};
	test_forward_range<int>       r2(a, a);
	test_forward_range<int>       r3(a, a+1);
	test_bidirectional_range<int> r4{};
	test_bidirectional_range<int> r5(a, a+2);

	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r1)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r2)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r3)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r4)), bool>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::empty(r5)), bool>::value, "");

	return
		 hamon::ranges::empty(r1) &&
		 hamon::ranges::empty(r2) &&
		!hamon::ranges::empty(r3) &&
		 hamon::ranges::empty(r4) &&
		!hamon::ranges::empty(r5);
}

GTEST_TEST(RangesTest, EmptyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	                      EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
}

}	// namespace empty_test

}	// namespace hamon_ranges_test
