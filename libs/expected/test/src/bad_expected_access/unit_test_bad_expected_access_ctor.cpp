/**
 *	@file	unit_test_bad_expected_access_ctor.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	constexpr explicit bad_expected_access(E);
 */

#include <hamon/expected/bad_expected_access.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_default_constructible<hamon::bad_expected_access<int>>::value, "");
static_assert( hamon::is_constructible<hamon::bad_expected_access<int>, int>::value, "");
#if !defined(HAMON_USE_STD_EXPECTED)
static_assert( hamon::is_nothrow_constructible<hamon::bad_expected_access<int>, int>::value, "");
#endif
static_assert(!hamon::is_trivially_constructible<hamon::bad_expected_access<int>, int>::value, "");
static_assert(!hamon::is_implicitly_constructible<hamon::bad_expected_access<int>, int>::value, "");
