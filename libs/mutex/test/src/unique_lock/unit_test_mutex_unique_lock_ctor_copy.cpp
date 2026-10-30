/**
 *	@file	unit_test_mutex_unique_lock_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	unique_lock(const unique_lock&) = delete;
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctor_copy_test
{

static_assert(!hamon::is_copy_constructible_v<hamon::unique_lock<checking_mutex>>, "");

}	// namespace ctor_copy_test

}	// namespace hamon_unique_lock_test
