/**
 *	@file	unit_test_mutex_lock_guard_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/type_traits.hpp>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

static_assert(!hamon::is_default_constructible_v<hamon::lock_guard<MyMutex>>, "");

}	// namespace hamon_lock_guard_test
