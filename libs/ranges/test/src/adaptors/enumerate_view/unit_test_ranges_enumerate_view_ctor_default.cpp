﻿/**
 *	@file	unit_test_ranges_enumerate_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr enumerate_view() requires default_initializable<V> = default;
 */

#include <hamon/ranges/adaptors/enumerate_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace enumerate_view_test
{
namespace ctor_default_test
{

template <typename T>
struct NoDefaultCtor : hamon::ranges::view_base
{
	NoDefaultCtor() = delete;

	T* begin() const noexcept;
	T* end()   const noexcept;
};

template <typename T>
struct NoThrowOnDefaultCtor : hamon::ranges::view_base
{
	NoThrowOnDefaultCtor() noexcept {}

	T* begin() const noexcept;
	T* end()   const noexcept;
};

static_assert( hamon::is_default_constructible<hamon::ranges::enumerate_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::enumerate_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::enumerate_view<NoThrowOnDefaultCtor<int>>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::enumerate_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::ranges::enumerate_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::enumerate_view<NoThrowOnDefaultCtor<int>>>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::enumerate_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::enumerate_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::enumerate_view<NoThrowOnDefaultCtor<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using EV = hamon::ranges::enumerate_view<V>;
	EV ev{};
	VERIFY(ev.begin() == ev.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, EnumerateViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace enumerate_view_test
}	// namespace hamon_ranges_test
