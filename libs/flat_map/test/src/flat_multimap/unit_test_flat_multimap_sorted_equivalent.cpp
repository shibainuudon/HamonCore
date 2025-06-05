/**
 *	@file	unit_test_flat_multimap_sorted_equivalent.cpp
 *
 *	@brief	sorted_equivalent のテスト
 *
 *	struct sorted_equivalent_t { explicit sorted_equivalent_t() = default; };
 *	inline constexpr sorted_equivalent_t sorted_equivalent{};
 */

#include <hamon/flat_map.hpp>
#include <hamon/type_traits.hpp>

static_assert( hamon::is_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert( hamon::is_trivially_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert(!hamon::is_implicitly_default_constructible<hamon::sorted_equivalent_t>::value, "");
static_assert( hamon::is_same<decltype(hamon::sorted_equivalent), hamon::sorted_equivalent_t const>::value, "");
