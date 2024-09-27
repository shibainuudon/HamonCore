/**
 *	@file	unit_test_atomic_detail_atomic_fetch_and.cpp
 *
 *	@brief	atomic_fetch_and のテスト
 */

#include <hamon/atomic/detail/atomic_fetch_and.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_fetch_and_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 0x0b;
		T y = 0x0e;
		auto before = hamon::detail::atomic_fetch_and(&x, y);
		EXPECT_EQ(T(0x0b), before);
		EXPECT_EQ(T(0x0a), x);
	}
	{
		T x = 0x5b;
		T y = 0x77;
		auto before = hamon::detail::atomic_fetch_and(&x, y, order);
		EXPECT_EQ(T(0x5b), before);
		EXPECT_EQ(T(0x53), x);
	}
}

GTEST_TEST(Atomic, AtomicFetchAndTest)
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

	{
		std::uint32_t x = 0xffffffff;
		std::thread t1{[&x]{
			hamon::detail::atomic_fetch_and(&x, std::uint32_t(0xffffff00));
		}};
		std::thread t2{[&x]{
			hamon::detail::atomic_fetch_and(&x, std::uint32_t(0x00ffffff));
		}};
		t1.join();
		t2.join();
		EXPECT_EQ(std::uint32_t(0x00ffff00), x);
	}
}

}	// namespace atomic_fetch_and_test

}	// namespace hamon_atomic_test
