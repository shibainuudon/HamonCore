/**
 *	@file	unit_test_mutex_lock_guard_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	lock_guard& operator=(const lock_guard&) = delete;
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/type_traits.hpp>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

static_assert(!hamon::is_copy_assignable_v<hamon::lock_guard<MyMutex>>, "");

}	// namespace hamon_lock_guard_test
