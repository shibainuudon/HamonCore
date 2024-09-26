/**
 *	@file	unit_test_atomic_detail_atomic_load.cpp
 *
 *	@brief	atomic_load のテスト
 */

#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>

namespace hamon_atomic_test
{

namespace atomic_load_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 1;
		T result = hamon::detail::atomic_load(&x);
		EXPECT_EQ(T(1), result);
	}
	{
		T x = 2;
		T result = hamon::detail::atomic_load(&x, order);
		EXPECT_EQ(T(2), result);
	}
}

GTEST_TEST(Atomic, AtomicLoadTest)
{
	test<signed char>(hamon::memory_order::relaxed);
	test<unsigned char>(hamon::memory_order::consume);
	test<short>(hamon::memory_order::acquire);
	test<unsigned short>(hamon::memory_order::release);
	test<int>(hamon::memory_order::acq_rel);
	test<unsigned int>(hamon::memory_order::seq_cst);
	test<long>(hamon::memory_order::relaxed);
	test<unsigned long>(hamon::memory_order::consume);
	test<long long>(hamon::memory_order::acquire);
	test<unsigned long long>(hamon::memory_order::release);
}

}	// namespace atomic_load_test

}	// namespace hamon_atomic_test
