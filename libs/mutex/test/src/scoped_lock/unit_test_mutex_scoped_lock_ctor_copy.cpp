/**
 *	@file	unit_test_mutex_scoped_lock_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	scoped_lock(const scoped_lock&) = delete;
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>

namespace hamon_scoped_lock_test
{

static_assert(!hamon::is_copy_constructible_v<hamon::scoped_lock<>>, "");
static_assert(!hamon::is_copy_constructible_v<hamon::scoped_lock<hamon::mutex>>, "");
static_assert(!hamon::is_copy_constructible_v<hamon::scoped_lock<hamon::mutex, hamon::mutex>>, "");

}	// namespace hamon_scoped_lock_test
