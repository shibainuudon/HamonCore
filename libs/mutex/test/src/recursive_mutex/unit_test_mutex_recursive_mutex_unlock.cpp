/**
 *	@file	unit_test_mutex_recursive_mutex_unlock.cpp
 *
 *	@brief	unlock のテスト
 *
 *	void unlock();
 */

#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::recursive_mutex>().unlock()), void>, "");
static_assert(!noexcept(hamon::declval<hamon::recursive_mutex>().unlock()), "");
