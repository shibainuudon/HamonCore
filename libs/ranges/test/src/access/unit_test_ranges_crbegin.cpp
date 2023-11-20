/**
 *	@file	unit_test_ranges_crbegin.cpp
 *
 *	@brief	ranges::crbegin のテスト
 */

#include <hamon/ranges/crbegin.hpp>
#include <hamon/ranges/rbegin.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/detail/constant_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace crbegin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR char      * begin()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char const* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char      * end()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char const* end() const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR int      * rbegin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int const* rbegin() const noexcept { return a + 1; }
	HAMON_CXX14_CONSTEXPR int      * rend()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int const* rend() const noexcept { return a + 4; }

	HAMON_CXX14_CONSTEXPR int const* crbegin() const noexcept { return nullptr; }
};

struct R2
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR char* begin()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end() const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR int* rbegin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* rbegin() const noexcept { return const_cast<int*>(a + 1); }
	HAMON_CXX14_CONSTEXPR int* rend()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int* rend() const noexcept { return const_cast<int*>(a + 4); }

	HAMON_CXX14_CONSTEXPR int* crbegin() const noexcept { return nullptr; }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(a)), hamon::reverse_iterator<int const*>>::value, "");
	static_assert(noexcept(hamon::ranges::crbegin(a)), "");
	VERIFY(hamon::ranges::crbegin(a) == hamon::ranges::rbegin(a));

	// [range.access.crbegin]/2
	{
		using I = decltype(hamon::ranges::crbegin(a));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(a)), hamon::reverse_iterator<int const*>>::value, "");
	static_assert(noexcept(hamon::ranges::crbegin(a)), "");
	VERIFY(hamon::ranges::crbegin(a) == hamon::ranges::rbegin(a));

	// [range.access.crbegin]/2
	{
		using I = decltype(hamon::ranges::crbegin(a));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r;
	R1 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(cr)), const int*>::value, "");

	// const& にキャストされてrbeginを呼び出す
	// メンバ関数crbeginは呼び出されない
	VERIFY(hamon::ranges::crbegin(r) != r.rbegin());
	VERIFY(hamon::ranges::crbegin(r) == cr.rbegin());
	VERIFY(hamon::ranges::crbegin(r) != r.crbegin());
	VERIFY(hamon::ranges::crbegin(cr) != r.rbegin());
	VERIFY(hamon::ranges::crbegin(cr) == cr.rbegin());
	VERIFY(hamon::ranges::crbegin(cr) != r.crbegin());

	// [range.access.crbegin]/2
	{
		using I = decltype(hamon::ranges::crbegin(r));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}
	{
		using I = decltype(hamon::ranges::crbegin(cr));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R2 r;
	R2 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(r)), hamon::basic_const_iterator<int*>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::crbegin(cr)), hamon::basic_const_iterator<int*>>::value, "");

	// const& にキャストしてもconstant_iteratorを返さないので、
	// 非const 版の結果をbasic_const_iteratorに変換する。
	// メンバ関数crbeginは呼び出されない
	VERIFY(hamon::ranges::crbegin(r) == r.rbegin());
	VERIFY(hamon::ranges::crbegin(r) != cr.rbegin());
	VERIFY(hamon::ranges::crbegin(r) != r.crbegin());
	VERIFY(hamon::ranges::crbegin(cr) != r.rbegin());
	VERIFY(hamon::ranges::crbegin(cr) == cr.rbegin());
	VERIFY(hamon::ranges::crbegin(cr) != r.crbegin());
	
	// [range.access.crbegin]/2
	{
		using I = decltype(hamon::ranges::crbegin(r));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}
	{
		using I = decltype(hamon::ranges::crbegin(cr));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CRBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace crbegin_test

}	// namespace hamon_ranges_test
