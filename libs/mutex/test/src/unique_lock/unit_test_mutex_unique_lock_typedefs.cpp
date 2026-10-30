/**
 *	@file	unit_test_mutex_unique_lock_typedefs.cpp
 *
 *	@brief
 *
 *	using mutex_type = Mutex;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace typedefs_test
{

static_assert(hamon::is_same_v<hamon::unique_lock<hamon::mutex>::mutex_type, hamon::mutex>, "");
static_assert(hamon::is_same_v<hamon::unique_lock<checking_mutex>::mutex_type, checking_mutex>, "");

}	// namespace typedefs_test

}	// namespace hamon_unique_lock_test
