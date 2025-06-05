/**
 *	@file	unit_test_flat_map_sorted_unique.cpp
 *
 *	@brief	sorted_unique のテスト
 *
 *	struct sorted_unique_t { explicit sorted_unique_t() = default; };
 *	inline constexpr sorted_unique_t sorted_unique{};
 */

#include <hamon/flat_map.hpp>
#include <hamon/type_traits.hpp>

static_assert( hamon::is_default_constructible<hamon::sorted_unique_t>::value, "");
static_assert( hamon::is_trivially_default_constructible<hamon::sorted_unique_t>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::sorted_unique_t>::value, "");
static_assert( hamon::is_same<decltype(hamon::sorted_unique), hamon::sorted_unique_t const>::value, "");
