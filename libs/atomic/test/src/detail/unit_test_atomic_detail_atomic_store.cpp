/**
 *	@file	unit_test_atomic_detail_atomic_store.cpp
 *
 *	@brief	atomic_store のテスト
 */

#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>

namespace hamon_atomic_test
{

namespace atomic_store_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 1;
		hamon::detail::atomic_store(&x, T(2));
		EXPECT_EQ(T(2), x);
	}
	{
		T x = 4;
		hamon::detail::atomic_store(&x, T(3), order);
		EXPECT_EQ(T(3), x);
	}
}

GTEST_TEST(Atomic, AtomicStoreTest)
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

}	// namespace atomic_store_test

}	// namespace hamon_atomic_test
