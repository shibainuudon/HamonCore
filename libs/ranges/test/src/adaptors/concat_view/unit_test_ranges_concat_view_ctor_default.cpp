/**
 *	@file	unit_test_ranges_concat_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr concat_view() = default;
 */

#include <hamon/ranges/adaptors/concat_view.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace concat_view_test
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

static_assert( hamon::is_default_constructible<hamon::ranges::concat_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::concat_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::concat_view<NoThrowOnDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::concat_view<test_input_view<int>, test_input_view<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::concat_view<NoDefaultCtor<int>,   test_input_view<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::concat_view<test_input_view<int>, NoDefaultCtor<int>,   test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::concat_view<test_input_view<int>, test_input_view<int>, NoDefaultCtor<int>>>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<NoThrowOnDefaultCtor<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<test_input_view<int>,      test_input_view<int>,      test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<NoThrowOnDefaultCtor<int>, test_input_view<int>,      test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<test_input_view<int>,      NoThrowOnDefaultCtor<int>, test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<test_input_view<int>,      test_input_view<int>,      NoThrowOnDefaultCtor<int>>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::concat_view<NoThrowOnDefaultCtor<int>, NoThrowOnDefaultCtor<int>, NoThrowOnDefaultCtor<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using CV = hamon::ranges::concat_view<test_forward_view<int>, test_forward_view<int>>;
	CV cv{};
	VERIFY(cv.empty());
	VERIFY(cv.begin() == cv.end());
	VERIFY(cv.cbegin() == cv.cend());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	hamon::ranges::concat_view<hamon::ranges::empty_view<char>> cv{};
    VERIFY(hamon::ranges::equal(cv, hamon::views::empty<char>));
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ConcatViewCtorDefaultTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_default_test
}	// namespace concat_view_test
}	// namespace hamon_ranges_test
