/**
 *	@file	unit_test_mutex_timed_mutex_unlock.cpp
 *
 *	@brief	unlock のテスト
 *
 *	void unlock();
 */

#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::timed_mutex>().unlock()), void>, "");
//static_assert(!noexcept(hamon::declval<hamon::timed_mutex>().unlock()), "");	// TODO
