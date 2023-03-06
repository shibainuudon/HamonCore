/**
 *	@file	unit_test_functional_identity.cpp
 *
 *	@brief	identity のテスト
 */

#include <hamon/functional/identity.hpp>
#include <hamon/type_traits/is_invocable.hpp>
#include <hamon/type_traits/is_nothrow_invocable_r.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/memory/addressof.hpp>
#include <type_traits>

namespace hamon_functional_test
{

namespace identity_test
{

static_assert( hamon::is_default_constructible<hamon::identity>::value, "");
static_assert( hamon::is_copy_constructible<hamon::identity>::value, "");
static_assert( hamon::is_move_constructible<hamon::identity>::value, "");
static_assert( std::is_copy_assignable<hamon::identity>::value, "");
static_assert( std::is_move_assignable<hamon::identity>::value, "");

static_assert(!hamon::is_invocable<hamon::identity>::value, "");
static_assert(!hamon::is_invocable<hamon::identity, int&, int&>::value, "");
static_assert( hamon::is_nothrow_invocable_r<int&, hamon::identity&, int&>::value, "");
static_assert( hamon::is_nothrow_invocable_r<const long&, hamon::identity, const long&>::value, "");
static_assert( hamon::is_nothrow_invocable_r<short&&, const hamon::identity&, short>::value, "");
static_assert( hamon::is_nothrow_invocable_r<const char&&, const hamon::identity, const char>::value, "");

int i;
static_assert( hamon::addressof(hamon::identity{}(i)) == hamon::addressof(i), "");

using T = hamon::identity::is_transparent; // required typedef

}	// namespace identity_test

}	// namespace hamon_functional_test
