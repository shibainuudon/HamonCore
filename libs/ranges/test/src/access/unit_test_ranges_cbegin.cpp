/**
 *	@file	unit_test_ranges_cbegin.cpp
 *
 *	@brief	ranges::cbegin のテスト
 */

#include <hamon/ranges/cbegin.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/detail/constant_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cbegin_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int      * begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int const* begin() const noexcept { return a + 1; }
	HAMON_CXX14_CONSTEXPR int const* cbegin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR int      * end()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int const* end() const noexcept { return a + 4; }
};

struct R2
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int* begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* begin() const noexcept { return const_cast<int*>(a + 1); }
	HAMON_CXX14_CONSTEXPR int* cbegin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR int* end()       noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int* end() const noexcept { return const_cast<int*>(a + 4); }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cbegin(a)), "");
	VERIFY(hamon::ranges::cbegin(a) == (a + 0));

	// [range.access.cbegin]/2
	{
		using I = decltype(hamon::ranges::cbegin(a));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cbegin(a)), "");
	VERIFY(hamon::ranges::cbegin(a) == (a + 0));

	// [range.access.cbegin]/2
	{
		using I = decltype(hamon::ranges::cbegin(a));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r;
	R1 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(cr)), const int*>::value, "");

	// const& にキャストされてbeginを呼び出す
	// メンバ関数cbeginは呼び出されない
	VERIFY(hamon::ranges::cbegin(r) != r.begin());
	VERIFY(hamon::ranges::cbegin(r) == cr.begin());
	VERIFY(hamon::ranges::cbegin(r) != r.cbegin());
	VERIFY(hamon::ranges::cbegin(cr) != r.begin());
	VERIFY(hamon::ranges::cbegin(cr) == cr.begin());
	VERIFY(hamon::ranges::cbegin(cr) != r.cbegin());

	// [range.access.cbegin]/2
	{
		using I = decltype(hamon::ranges::cbegin(r));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}
	{
		using I = decltype(hamon::ranges::cbegin(cr));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R2 r;
	R2 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(r)), hamon::basic_const_iterator<int*>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cbegin(cr)), hamon::basic_const_iterator<int*>>::value, "");

	// const& にキャストしてもconstant_iteratorを返さないので、
	// 非const 版の結果をbasic_const_iteratorに変換する。
	// メンバ関数cbeginは呼び出されない
	VERIFY(hamon::ranges::cbegin(r) == r.begin());
	VERIFY(hamon::ranges::cbegin(r) != cr.begin());
	VERIFY(hamon::ranges::cbegin(r) != r.cbegin());
	VERIFY(hamon::ranges::cbegin(cr) != r.begin());
	VERIFY(hamon::ranges::cbegin(cr) == cr.begin());
	VERIFY(hamon::ranges::cbegin(cr) != r.cbegin());
	
	// [range.access.cbegin]/2
	{
		using I = decltype(hamon::ranges::cbegin(r));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}
	{
		using I = decltype(hamon::ranges::cbegin(cr));
		static_assert(hamon::input_or_output_iterator_t<I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<I>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CBeginTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace cbegin_test

}	// namespace hamon_ranges_test
