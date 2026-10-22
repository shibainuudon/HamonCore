/**
 *	@file	unit_test_thread_hardware_concurrency.cpp
 *
 *	@brief	hardware_concurrency のテスト
 *
 *	unsigned hardware_concurrency() noexcept;
 */

#include <hamon/thread/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_thread_test
{

namespace hardware_concurrency_test
{

GTEST_TEST(ThreadTest, HardwareConcurrencyTest)
{
	static_assert(noexcept(hamon::thread::hardware_concurrency()), "");
	static_assert(hamon::is_same_v<decltype(hamon::thread::hardware_concurrency()), unsigned int>, "");

	EXPECT_EQ(
		hamon::thread::hardware_concurrency(),
		hamon::thread::hardware_concurrency());
}

}	// namespace hardware_concurrency_test

}	// namespace hamon_thread_test
