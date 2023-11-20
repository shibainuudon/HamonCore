/**
 *	@file	unit_test_ranges_crend.cpp
 *
 *	@brief	ranges::crend のテスト
 */

#include <hamon/ranges/crend.hpp>
#include <hamon/ranges/rend.hpp>
#include <hamon/ranges/crbegin.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/detail/constant_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_ranges_test
{

namespace crend_test
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
	HAMON_CXX14_CONSTEXPR int const* rbegin() const noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int      * rend()       noexcept { return a + 3; }
	HAMON_CXX14_CONSTEXPR int const* rend() const noexcept { return a + 4; }

	HAMON_CXX14_CONSTEXPR int const* crend() const noexcept { return nullptr; }
};

struct R2
{
	int a[4] = { 0, 1, 2, 3 };

	HAMON_CXX14_CONSTEXPR char* begin()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* begin() const noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end()       noexcept { return nullptr; }
	HAMON_CXX14_CONSTEXPR char* end() const noexcept { return nullptr; }

	HAMON_CXX14_CONSTEXPR int* rbegin()       noexcept { return a + 0; }
	HAMON_CXX14_CONSTEXPR int* rbegin() const noexcept { return const_cast<int*>(a + 0); }
	HAMON_CXX14_CONSTEXPR int* rend()       noexcept { return a + 3; }
	HAMON_CXX14_CONSTEXPR int* rend() const noexcept { return const_cast<int*>(a + 4); }

	HAMON_CXX14_CONSTEXPR int* crend() const noexcept { return nullptr; }
};

HAMON_CXX14_CONSTEXPR bool test01()
{
	int const a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(a)), hamon::reverse_iterator<int const*>>::value, "");
	static_assert(noexcept(hamon::ranges::crend(a)), "");
	VERIFY(hamon::ranges::crend(a) == hamon::ranges::rend(a));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	int a[2] = {};

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(a)), hamon::reverse_iterator<int const*>>::value, "");
	static_assert(noexcept(hamon::ranges::crend(a)), "");
	VERIFY(hamon::ranges::crend(a) == hamon::ranges::rend(a));

	return true;
}

HAMON_CXX14_CONSTEXPR bool test03()
{
	R1 r;
	R1 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(r)), const int*>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(cr)), const int*>::value, "");

	// const& にキャストされてrendを呼び出す
	// メンバ関数crendは呼び出されない
	VERIFY(hamon::ranges::crend(r) != r.rend());
	VERIFY(hamon::ranges::crend(r) == cr.rend());
	VERIFY(hamon::ranges::crend(r) != r.crend());
	VERIFY(hamon::ranges::crend(cr) != r.rend());
	VERIFY(hamon::ranges::crend(cr) == cr.rend());
	VERIFY(hamon::ranges::crend(cr) != r.crend());

	// [range.access.crend]/2
	{
		using I = decltype(hamon::ranges::crbegin(r));
		using S = decltype(hamon::ranges::crend(r));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}
	{
		using I = decltype(hamon::ranges::crbegin(cr));
		using S = decltype(hamon::ranges::crend(cr));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool test04()
{
	R2 r;
	R2 const& cr = r;

	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(r)), hamon::basic_const_iterator<int*>>::value, "");
	static_assert(hamon::same_as_t<decltype(hamon::ranges::crend(cr)), hamon::basic_const_iterator<int*>>::value, "");

	// const& にキャストしてもconstant_iteratorを返さないので、
	// 非const 版の結果をbasic_const_iteratorに変換する。
	// メンバ関数crendは呼び出されない
	VERIFY(hamon::ranges::crend(r) == r.rend());
	VERIFY(hamon::ranges::crend(r) != cr.rend());
	VERIFY(hamon::ranges::crend(r) != r.crend());
	VERIFY(hamon::ranges::crend(cr) != r.rend());
	VERIFY(hamon::ranges::crend(cr) == cr.rend());
	VERIFY(hamon::ranges::crend(cr) != r.crend());

	// [range.access.crend]/2
	{
		using I = decltype(hamon::ranges::crbegin(r));
		using S = decltype(hamon::ranges::crend(r));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}
	{
		using I = decltype(hamon::ranges::crbegin(cr));
		using S = decltype(hamon::ranges::crend(cr));
		static_assert(hamon::sentinel_for_t<S, I>::value, "");
		static_assert(hamon::detail::constant_iterator_t<S>::value, "");
	}

	return true;
}

GTEST_TEST(RangesTest, CREndTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(test02());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test03());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test04());
}

#undef VERIFY

}	// namespace crend_test

}	// namespace hamon_ranges_test
