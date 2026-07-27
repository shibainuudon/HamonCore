/**
 *	@file	unit_test_ranges_as_input_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	as_input_view() requires default_initializable<V> = default;
 */

#include <hamon/ranges/adaptors/as_input_view.hpp>
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
namespace as_input_view_test
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

static_assert( hamon::is_default_constructible<hamon::ranges::as_input_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_default_constructible<hamon::ranges::as_input_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_default_constructible<hamon::ranges::as_input_view<NoThrowOnDefaultCtor<int>>>::value, "");

static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::as_input_view<test_input_view<int>>>::value, "");
static_assert(!hamon::is_nothrow_default_constructible<hamon::ranges::as_input_view<NoDefaultCtor<int>>>::value, "");
static_assert( hamon::is_nothrow_default_constructible<hamon::ranges::as_input_view<NoThrowOnDefaultCtor<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using AIV = hamon::ranges::as_input_view<test_random_access_view<int>>;
	AIV aiv{};
	VERIFY(aiv.empty());
	VERIFY(aiv.begin() == aiv.end());
	VERIFY(aiv.cbegin() == aiv.cend());
	return true;
}

HAMON_CXX14_CONSTEXPR bool test01()
{
	hamon::ranges::as_input_view<hamon::ranges::empty_view<char>> aiv{};
    VERIFY(hamon::ranges::equal(aiv, hamon::views::empty<char>));
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, AsInputViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace ctor_default_test
}	// namespace as_input_view_test
}	// namespace hamon_ranges_test
