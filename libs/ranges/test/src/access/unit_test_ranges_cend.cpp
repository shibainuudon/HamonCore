/**
 *	@file	unit_test_ranges_cend.cpp
 *
 *	@brief	ranges::cend のテスト
 */

#include <hamon/ranges/cend.hpp>
#include <hamon/ranges/cbegin.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/detail/constant_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace cend_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct R1
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int      * begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int const* begin() const noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int      * end()       noexcept { return a + 3; }
	HAMON_CXX14_CONSTEXPR int const* end() const noexcept { return a + 4; }
	HAMON_CXX14_CONSTEXPR int const* cend() const noexcept { return nullptr; }
};

struct R2
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR int* begin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* begin() const noexcept { return const_cast<int*>(a + 0); }
	HAMON_CXX14_CONSTEXPR int* end()       noexcept { return a + 3; }
	HAMON_CXX14_CONSTEXPR int* end() const noexcept { return const_cast<int*>(a + 4); }
	HAMON_CXX14_CONSTEXPR int* cend() const noexcept { return nullptr; }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cend(a)), "");
	VERIFY(hamon::ranges::cend(a) == (a + 2));

	// [range.access.cend]/2
	{
		using I = decltype(hamon::ranges::cbegin(a));
		using S = decltype(hamon::ranges::cend(a));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(a)), const int*>::value, "");
	static_assert(noexcept(hamon::ranges::cend(a)), "");
	VERIFY(hamon::ranges::cend(a) == (a + 2));

	// [range.access.cend]/2
	{
		using I = decltype(hamon::ranges::cbegin(a));
		using S = decltype(hamon::ranges::cend(a));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r;
	R1 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(cr)), const int*>::value, "");

	// const& にキャストされてendを呼び出す
	// メンバ関数cendは呼び出されない
	VERIFY(hamon::ranges::cend(r) != r.end());
	VERIFY(hamon::ranges::cend(r) == cr.end());
	VERIFY(hamon::ranges::cend(r) != r.cend());
	VERIFY(hamon::ranges::cend(cr) != r.end());
	VERIFY(hamon::ranges::cend(cr) == cr.end());
	VERIFY(hamon::ranges::cend(cr) != r.cend());

	// [range.access.cend]/2
	{
		using I = decltype(hamon::ranges::cbegin(r));
		using S = decltype(hamon::ranges::cend(r));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}
	{
		using I = decltype(hamon::ranges::cbegin(cr));
		using S = decltype(hamon::ranges::cend(cr));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R2 r;
	R2 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(r)), hamon::basic_const_iterator<int*>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::cend(cr)), hamon::basic_const_iterator<int*>>::value, "");

	// const& にキャストしてもconstant_iteratorを返さないので、
	// 非const 版の結果をbasic_const_iteratorに変換する。
	// メンバ関数cendは呼び出されない
	VERIFY(hamon::ranges::cend(r) == r.end());
	VERIFY(hamon::ranges::cend(r) != cr.end());
	VERIFY(hamon::ranges::cend(r) != r.cend());
	VERIFY(hamon::ranges::cend(cr) != r.end());
	VERIFY(hamon::ranges::cend(cr) == cr.end());
	VERIFY(hamon::ranges::cend(cr) != r.cend());
	
	// [range.access.cend]/2
	{
		using I = decltype(hamon::ranges::cbegin(r));
		using S = decltype(hamon::ranges::cend(r));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}
	{
		using I = decltype(hamon::ranges::cbegin(cr));
		using S = decltype(hamon::ranges::cend(cr));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CEndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

}	// namespace cend_test

}	// namespace hamon_ranges_test
