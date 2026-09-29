/**
 *	@file	unit_test_atomic_atomic_signal_fence.cpp
 *
 *	@brief	atomic_signal_fence のテスト
 */

#include <hamon/atomic/atomic_signal_fence.hpp>
#include <hamon/atomic/atomic.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_atomic_test
{
namespace atomic_signal_fence_test
{

inline HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	hamon::atomic_signal_fence(hamon::memory_order::relaxed);
	hamon::atomic_signal_fence(hamon::memory_order::acquire);
	hamon::atomic_signal_fence(hamon::memory_order::release);
	hamon::atomic_signal_fence(hamon::memory_order::acq_rel);
	hamon::atomic_signal_fence(hamon::memory_order::seq_cst);
	return true;
}

GTEST_TEST(Atomic, AtomicSignalFenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test());
}

}	// namespace atomic_signal_fence_test
}	// namespace hamon_atomic_test
