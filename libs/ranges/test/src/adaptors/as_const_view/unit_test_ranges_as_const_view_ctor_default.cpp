/**
 *	@file	unit_test_ranges_as_const_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	as_const_view() requires default_initializable<V> = default;
 */

#include <hamon/ranges/adaptors/as_const_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace as_const_view_test
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

// is_default_constructible
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::as_const_view<test_input_view<int>>
	>::value == true, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::as_const_view<NoDefaultCtor<int>>
	>::value == false, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::as_const_view<NoThrowOnDefaultCtor<int>>
	>::value == true, "");

// is_implicitly_default_constructible
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::as_const_view<test_input_view<int>>
	>::value == true, "");
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::as_const_view<NoDefaultCtor<int>>
	>::value == false, "");
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::as_const_view<NoThrowOnDefaultCtor<int>>
	>::value == true, "");

// is_nothrow_default_constructible
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::as_const_view<test_input_view<int>>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::as_const_view<NoDefaultCtor<int>>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::as_const_view<NoThrowOnDefaultCtor<int>>
	>::value == true, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<int>;
	using CV = hamon::ranges::as_const_view<V>;
	CV cv{};
	VERIFY(cv.begin() == cv.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsConstViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace as_const_view_test
}	// namespace hamon_ranges_test
