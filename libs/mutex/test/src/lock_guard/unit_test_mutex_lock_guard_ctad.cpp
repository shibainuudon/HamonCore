/**
 *	@file	unit_test_mutex_lock_guard_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 */

#include <hamon/mutex/lock_guard.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "lock_guard_test_helper.hpp"

namespace hamon_lock_guard_test
{

namespace ctad_test
{

GTEST_TEST(LockGuardTest, CtadTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		MyMutex m;
		hamon::lock_guard lg(m);
		static_assert(hamon::is_same_v<decltype(lg), hamon::lock_guard<MyMutex>>, "");
	}
	{
		hamon::mutex m;
		hamon::lock_guard lg(m);
		static_assert(hamon::is_same_v<decltype(lg), hamon::lock_guard<hamon::mutex>>, "");
	}
#endif
}

}	// namespace ctad_test

}	// namespace hamon_lock_guard_test
