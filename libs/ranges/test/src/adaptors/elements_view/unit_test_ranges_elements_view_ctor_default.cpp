/**
 *	@file	unit_test_ranges_elements_view_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	elements_view() requires default_initializable<V> = default;
 */

#include <hamon/ranges/adaptors/elements_view.hpp>
#include <hamon/ranges/view_base.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_implicitly_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_ranges_test
{
namespace elements_view_test
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
		hamon::ranges::elements_view<test_input_view<hamon::tuple<int, long>>, 0>
	>::value == true, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::elements_view<NoDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == false, "");
static_assert(
	hamon::is_default_constructible<
		hamon::ranges::elements_view<NoThrowOnDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == true, "");

// is_implicitly_default_constructible
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::elements_view<test_input_view<hamon::tuple<int, long>>, 0>
	>::value == true, "");
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::elements_view<NoDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == false, "");
static_assert(
	hamon::is_implicitly_default_constructible<
		hamon::ranges::elements_view<NoThrowOnDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == true, "");

// is_nothrow_default_constructible
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::elements_view<test_input_view<hamon::tuple<int, long>>, 0>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::elements_view<NoDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == false, "");
static_assert(
	hamon::is_nothrow_default_constructible<
		hamon::ranges::elements_view<NoThrowOnDefaultCtor<hamon::tuple<int, long>>, 0>
	>::value == true, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using V = test_input_view<hamon::tuple<int, long>>;
	using EV = hamon::ranges::elements_view<V, 0>;
	EV ev{};
	VERIFY(ev.begin() == ev.end());
	return true;
}

#undef VERIFY

GTEST_TEST(RangesTest, ElementsViewCtorDefaultTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace ctor_default_test
}	// namespace elements_view_test
}	// namespace hamon_ranges_test
