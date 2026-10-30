/**
 *	@file	unit_test_mutex_lock_guard_typedefs.cpp
 *
 *	@brief
 *
 *	using mutex_type = Mutex;
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/type_traits.hpp>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

static_assert(hamon::is_same_v<hamon::lock_guard<MyMutex>::mutex_type, MyMutex>, "");

}	// namespace hamon_lock_guard_test
