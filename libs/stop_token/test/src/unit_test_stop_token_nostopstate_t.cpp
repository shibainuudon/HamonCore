/**
 *	@file	unit_test_stop_token_nostopstate_t.cpp
 *
 *	@brief	nostopstate_t のテスト
 *
 *	struct nostopstate_t {
 *		explicit nostopstate_t() = default;
 *	};
 *	inline constexpr nostopstate_t nostopstate{};
 */

#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace nostopstate_t_test
{

static_assert( hamon::is_default_constructible_v<hamon::nostopstate_t>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::nostopstate_t>, "");
static_assert( hamon::is_trivially_default_constructible_v<hamon::nostopstate_t>, "");
static_assert(!hamon::is_implicitly_default_constructible_v<hamon::nostopstate_t>, "");

static_assert(hamon::is_empty_v<hamon::nostopstate_t>, "");

static_assert(hamon::is_same_v<decltype(hamon::nostopstate), hamon::nostopstate_t const>, "");

}	// namespace nostopstate_t_test

}	// namespace hamon_stop_token_test
