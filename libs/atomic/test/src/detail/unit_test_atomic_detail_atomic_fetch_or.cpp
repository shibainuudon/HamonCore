/**
 *	@file	unit_test_atomic_detail_atomic_fetch_or.cpp
 *
 *	@brief	atomic_fetch_or のテスト
 */

#include <hamon/atomic/detail/atomic_fetch_or.hpp>
#include <hamon/atomic/memory_order.hpp>
#include <gtest/gtest.h>
#include <cstdint>
#include <thread>

namespace hamon_atomic_test
{

namespace atomic_fetch_or_test
{

template <typename T>
void test(hamon::memory_order order)
{
	{
		T x = 0x0b;
		T y = 0x0e;
		auto before = hamon::detail::atomic_fetch_or(&x, y);
		EXPECT_EQ(T(0x0b), before);
		EXPECT_EQ(T(0x0f), x);
	}
	{
		T x = 0x5b;
		T y = 0x77;
		auto before = hamon::detail::atomic_fetch_or(&x, y, order);
		EXPECT_EQ(T(0x5b), before);
		EXPECT_EQ(T(0x7f), x);
	}
}

GTEST_TEST(Atomic, AtomicFetchOrTest)
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
		std::uint32_t x = 0x00000000;
		std::thread t1{[&x]{
			hamon::detail::atomic_fetch_or(&x, std::uint32_t(0xf0f0f0f0));
		}};
		std::thread t2{[&x]{
			hamon::detail::atomic_fetch_or(&x, std::uint32_t(0x0000ffff));
		}};
		t1.join();
		t2.join();
		EXPECT_EQ(std::uint32_t(0xf0f0ffff), x);
	}
}

}	// namespace atomic_fetch_or_test

}	// namespace hamon_atomic_test
