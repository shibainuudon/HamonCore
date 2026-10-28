/**
 *	@file	unit_test_thread_jthread_hardware_concurrency.cpp
 *
 *	@brief	hardware_concurrency のテスト
 *
 *	static unsigned int hardware_concurrency() noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace hardware_concurrency_test
{

GTEST_TEST(JThreadTest, HardwareConcurrencyTest)
{
	static_assert(noexcept(hamon::jthread::hardware_concurrency()), "");
	static_assert(hamon::is_same_v<decltype(hamon::jthread::hardware_concurrency()), unsigned int>, "");

	EXPECT_EQ(
		hamon::jthread::hardware_concurrency(),
		hamon::jthread::hardware_concurrency());
}

}	// namespace hardware_concurrency_test

}	// namespace hamon_jthread_test
