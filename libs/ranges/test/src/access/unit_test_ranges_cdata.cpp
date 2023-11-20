/**
 *	@file	unit_test_ranges_cdata.cpp
 *
 *	@brief	ranges::cdata のテスト
 */

#include <hamon/ranges/cdata.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cdata_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR char      * begin()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char const* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char      * end()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char const* end() const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR int      * data()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int const* data() const noexcept { return a + 1; }
};

struct R2
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR char* begin()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end() const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR int* data()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* data() const noexcept { return const_cast<int*>(a + 1); }
};

struct R3
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int      * begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int const* begin() const noexcept { return a + 1; }
	HAMON_CXX14_CONSTEXPR int      * end()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int const* end() const noexcept { return a + 4; }
};

struct R4
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int* begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* begin() const noexcept { return const_cast<int*>(a + 1); }
	HAMON_CXX14_CONSTEXPR int* end()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int* end() const noexcept { return const_cast<int*>(a + 4); }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cdata(a)), "");
	VERIFY(hamon::ranges::cdata(a) == (a + 0));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cdata(a)), "");
	VERIFY(hamon::ranges::cdata(a) == (a + 0));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r;
	R1 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(cr)), const int*>::value, "");

	// const& にキャストされてdataを呼び出す
	VERIFY(hamon::ranges::cdata(r) != r.data());
	VERIFY(hamon::ranges::cdata(r) == cr.data());
	VERIFY(hamon::ranges::cdata(cr) != r.data());
	VERIFY(hamon::ranges::cdata(cr) == cr.data());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R2 r;
	R2 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(cr)), const int*>::value, "");

	// R2がconstant_rangeでないので、
	// 非const版の結果をconstポインタに変換する。
	VERIFY(hamon::ranges::cdata(r) == r.data());
	VERIFY(hamon::ranges::cdata(r) != cr.data());
	VERIFY(hamon::ranges::cdata(cr) != r.data());
	VERIFY(hamon::ranges::cdata(cr) == cr.data());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test05()
{
	R3 r;
	R3 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(cr)), const int*>::value, "");

	// dataメンバ関数を持たないのでto_address(ranges::begin(r))を呼び出す
	VERIFY(hamon::ranges::cdata(r) != r.begin());
	VERIFY(hamon::ranges::cdata(r) == cr.begin());
	VERIFY(hamon::ranges::cdata(cr) != r.begin());
	VERIFY(hamon::ranges::cdata(cr) == cr.begin());

	return true;
}

HAMON_CXX14_CONSTEXPR bool test06()
{
	R4 r;
	R4 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cdata(cr)), const int*>::value, "");

	// dataメンバ関数を持たないのでto_address(ranges::begin(r))を呼び出す
	// R4がconstant_rangeでないので、
	// 非const版の結果をconstポインタに変換する。
	VERIFY(hamon::ranges::cdata(r) == r.begin());
	VERIFY(hamon::ranges::cdata(r) != cr.begin());
	VERIFY(hamon::ranges::cdata(cr) != r.begin());
	VERIFY(hamon::ranges::cdata(cr) == cr.begin());

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CDataTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test05());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test06());
}

}	// namespace cdata_test

}	// namespace hamon_ranges_test
