/**
 *	@file	unit_test_atomic_atomic_alias.cpp
 *
 *	@brief	[atomics.alias] のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>

static_assert(hamon::atomic_signed_lock_free::is_always_lock_free, "");
static_assert(hamon::atomic_unsigned_lock_free::is_always_lock_free, "");

static_assert(hamon::is_signed_v<typename hamon::atomic_signed_lock_free::value_type>, "");
static_assert(hamon::is_unsigned_v<typename hamon::atomic_unsigned_lock_free::value_type>, "");
