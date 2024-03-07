/**
 *	@file	unit_test_ranges_cartesian_product_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr cartesian_product_view() = default;
 */

#include <hamon/ranges/adaptors/cartesian_product_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace cartesian_product_view_test
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

static_assert( hamon::is_default_constructible<hamon::ranges::cartesian_product_view<test_input_view<int>>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::cartesian_product_view<NoDefaultCtor<int>>>::value == true, "");
static_assert( hamon::is_default_constructible<hamon::ranges::cartesian_product_view<NoThrowOnDefaultCtor<int>>>::value == true, "");
static_assert( hamon::is_default_constructible<hamon::ranges::cartesian_product_view<test_forward_view<int>, test_forward_view<int>>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::cartesian_product_view<NoDefaultCtor<int>,     test_forward_view<int>>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::cartesian_product_view<test_forward_view<int>, NoDefaultCtor<int>>>::value == true, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::cartesian_product_view<NoDefaultCtor<int>,     NoDefaultCtor<int>>>::value == true, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<test_input_view<int>>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<NoDefaultCtor<int>>>::value == true, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<NoThrowOnDefaultCtor<int>>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<test_forward_view<int>,    test_forward_view<int>>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<NoThrowOnDefaultCtor<int>, test_forward_view<int>>>::value == true, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<test_forward_view<int>,    NoThrowOnDefaultCtor<int>>>::value == true, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::cartesian_product_view<NoThrowOnDefaultCtor<int>, NoThrowOnDefaultCtor<int>>>::value == true, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using CV = hamon::ranges::cartesian_product_view<test_forward_view<int>, test_forward_view<int>>;
	CV cv{};
	VERIFY(cv.begin() == cv.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, CartesianProductViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace cartesian_product_view_test
}	// namespace hamon_ranges_test
