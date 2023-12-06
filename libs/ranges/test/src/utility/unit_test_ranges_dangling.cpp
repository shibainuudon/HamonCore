/**
 *	@file	unit_test_ranges_dangling.cpp
 *
 *	@brief	ranges::dangling のテスト
 */

#include <hamon/ranges/utility/dangling.hpp>
#include <hamon/type_traits/is_trivially_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>

// dangling is trivially default constructible.
static_assert(hamon::is_trivially_default_constructible<hamon::ranges::dangling>::value, "");

// dangling can be constructed from arguments of arbitrary number and arbitrary non-void type.
static_assert(hamon::is_nothrow_constructible<hamon::ranges::dangling, int>::value, "");
static_assert(hamon::is_nothrow_constructible<hamon::ranges::dangling, float>::value, "");
static_assert(hamon::is_nothrow_constructible<hamon::ranges::dangling, int, long>::value, "");
static_assert(hamon::is_nothrow_constructible<hamon::ranges::dangling, char, void*, const double&>::value, "");
