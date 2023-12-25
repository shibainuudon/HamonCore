/**
 *	@file	unit_test_ranges_join_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 * 
 *	join_view() requires default_initializable<V> = default;
 */

#include <hamon/ranges/adaptors/join_view.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace join_view_test
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
struct ThrowOnDefaultCtor : hamon::ranges::view_base
{
	ThrowOnDefaultCtor() {}

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
		hamon::ranges::join_view<test_input_view<test_input_view<int>>>
	>::value == true, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::join_view<NoDefaultCtor<test_input_view<int>>>
	>::value == false, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::join_view<test_input_view<NoDefaultCtor<int>>>
	>::value == true, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::join_view<ThrowOnDefaultCtor<test_input_view<int>>>
	>::value == true, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::join_view<test_input_view<ThrowOnDefaultCtor<int>>>
	>::value == true, "");

static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::join_view<test_input_view<test_input_view<int>>>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::join_view<NoDefaultCtor<test_input_view<int>>>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::join_view<test_input_view<NoDefaultCtor<int>>>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::join_view<NoThrowOnDefaultCtor<test_input_view<int>>>
	>::value == true, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::join_view<test_input_view<NoThrowOnDefaultCtor<int>>>
	>::value == false, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test()
{
	using V = test_input_view<test_input_view<int>>;
	using RV = hamon::ranges::join_view<V>;

	{
		RV rv{};
		VERIFY(rv.begin() == rv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, JoinViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace ctor_default_test
}	// namespace join_view_test
}	// namespace hamon_ranges_test
