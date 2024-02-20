/**
 *	@file	unit_test_ranges_zip_transform_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	zip_transform_view() = default;
 */

#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace zip_transform_view_test
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

struct F
{
	template <typename... Args>
	constexpr int operator()(Args&&...) const { return 0; }
};

static_assert( hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, NoThrowOnDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoThrowOnDefaultCtor<int>>>::value, "");

static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, NoThrowOnDefaultCtor<int>>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_implicitly_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoThrowOnDefaultCtor<int>>>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, NoThrowOnDefaultCtor<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoDefaultCtor<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::zip_transform_view<F, test_input_view<int>, NoThrowOnDefaultCtor<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	{
		using V = test_input_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V>;
		ZV zv{};
		VERIFY(zv.begin() == zv.end());
	}
	{
		using V1 = test_input_view<int>;
		using V2 = test_forward_view<int>;
		using ZV = hamon::ranges::zip_transform_view<F, V1, V2>;
		ZV zv{};
		VERIFY(zv.begin() == zv.end());
	}
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ZipTransformViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace zip_transform_view_test
}	// namespace hamon_ranges_test
