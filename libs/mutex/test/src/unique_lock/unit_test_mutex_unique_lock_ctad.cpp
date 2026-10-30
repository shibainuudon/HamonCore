/**
 *	@file	unit_test_mutex_unique_lock_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 */

#include <hamon/mutex/unique_lock.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "checking_mutex.hpp"

namespace hamon_unique_lock_test
{

namespace ctad_test
{

GTEST_TEST(UniqueLockTest, CtadTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	checking_mutex mux;
	hamon::unique_lock lk(mux);
	static_assert(hamon::is_same<decltype(lk), hamon::unique_lock<checking_mutex>>::value, "");
#endif
}

}	// namespace ctad_test

}	// namespace hamon_unique_lock_test
