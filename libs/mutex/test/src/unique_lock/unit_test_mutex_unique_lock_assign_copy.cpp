/**
 *	@file	unit_test_mutex_unique_lock_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	unique_lock& operator=(const unique_lock&) = delete;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace assign_copy_test
{

static_assert(!hamon::is_copy_assignable_v<hamon::unique_lock<checking_mutex>>, "");

}	// namespace assign_copy_test

}	// namespace hamon_unique_lock_test
