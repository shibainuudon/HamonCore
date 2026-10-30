/**
 *	@file	unit_test_mutex_scoped_lock_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 */

#include <hamon/mutex/scoped_lock.hpp>
#include <hamon/mutex/mutex.hpp>
#include <hamon/mutex/recursive_mutex.hpp>
#include <hamon/mutex/recursive_timed_mutex.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_scoped_lock_test
{

namespace ctad_test
{

GTEST_TEST(ScopedLockTest, CtadTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::mutex m;
		hamon::scoped_lock lk(m);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<hamon::mutex>>::value, "");
	}
	{
		hamon::mutex m1;
		hamon::recursive_mutex m2;
		hamon::scoped_lock lk(m1, m2);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<hamon::mutex, hamon::recursive_mutex>>::value, "");
	}
	{
		hamon::recursive_mutex m1;
		hamon::recursive_timed_mutex m2;
		hamon::mutex m3;
		hamon::scoped_lock lk(m1, m2, m3);
		static_assert(hamon::is_same<decltype(lk), hamon::scoped_lock<hamon::recursive_mutex, hamon::recursive_timed_mutex, hamon::mutex>>::value, "");
	}
#endif
}

}	// namespace ctad_test

}	// namespace hamon_scoped_lock_test
