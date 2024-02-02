/**
 *	@file	unit_test_ranges_split_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	split_view()
 *	  requires default_initializable<V> && default_initializable<Pattern> = default;
 */

#include <hamon/ranges/adaptors/split_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace split_view_test
{
namespace ctor_default_test
{

template <typename T>
struct NoDefaultCtor : hamon::ranges::view_base
{
	NoDefaultCtor() = delete;

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

template <typename T>
struct NoThrowOnDefaultCtor : hamon::ranges::view_base
{
	NoThrowOnDefaultCtor() noexcept {}

	HAMON_CXX11_CONSTEXPR T* begin() const noexcept { return nullptr; }
	HAMON_CXX11_CONSTEXPR T* end()   const noexcept { return nullptr; }
};

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, test_forward_view<int>>
	>::value == true, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<NoDefaultCtor<int>, test_forward_view<int>>
	>::value == false, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, NoDefaultCtor<int>>
	>::value == false, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<NoDefaultCtor<int>, NoDefaultCtor<int>>
	>::value == false, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<NoThrowOnDefaultCtor<int>, test_forward_view<int>>
	>::value == true, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, NoThrowOnDefaultCtor<int>>
	>::value == true, "");

static_assert(
	hamon::is_default_constructible<
		hamon::ranges::split_view<NoThrowOnDefaultCtor<int>, NoThrowOnDefaultCtor<int>>
	>::value == true, "");


static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, test_forward_view<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<NoDefaultCtor<int>, test_forward_view<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, NoDefaultCtor<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<NoDefaultCtor<int>, NoDefaultCtor<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<NoThrowOnDefaultCtor<int>, test_forward_view<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<test_forward_view<int>, NoThrowOnDefaultCtor<int>>
	>::value == false, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::split_view<NoThrowOnDefaultCtor<int>, NoThrowOnDefaultCtor<int>>
	>::value == true, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using RV = hamon::ranges::split_view<test_forward_view<int>, test_forward_view<int>>;
	RV rv{};
	VERIFY(rv.begin() == rv.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, SplitViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace split_view_test
}	// namespace hamon_ranges_test
