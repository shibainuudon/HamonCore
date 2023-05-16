/**
 *	@file	unit_test_optional_nullopt.cpp
 *
 *	@brief	nulloptのテスト
 *
 *	struct nullopt_t{see below};
 *	inline constexpr nullopt_t nullopt(unspecified);
 */

#include <hamon/optional.hpp>
#include <hamon/type_traits.hpp>

static_assert( hamon::is_same<decltype(hamon::nullopt), const hamon::nullopt_t>::value, "");

// [optional.nullopt]/1
// The struct nullopt_t is an empty class type
static_assert( hamon::is_empty<hamon::nullopt_t>::value, "");

// [optional.nullopt]/2
// Type nullopt_t shall not have a default constructor or
// an initializer-list constructor, and shall not be an aggregate.
static_assert(!hamon::is_default_constructible<hamon::nullopt_t>::value, "");
#if defined(HAMON_HAS_IS_AGGREGATE)
static_assert(!hamon::is_aggregate<hamon::nullopt_t>::value, "");
#endif
