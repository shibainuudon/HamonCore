/**
 *	@file	unit_test_atomic_atomic_integral.cpp
 *
 *	@brief	atomic のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_atomic_test
{
namespace atomic_integral_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	{
		hamon::atomic<T> a;
		VERIFY(a.load() == T(0));
	}
	{
		hamon::atomic<T> a(T(13));
		VERIFY(a.load() == T(13));
	}
	{
		hamon::atomic<T> a(T(1));
		a.store(T(2));
		VERIFY(a.load() == T(2));
	}
	return true;
}

template <typename T>
bool volatile_test()
{
	{
		hamon::atomic<T> volatile a;
		VERIFY(a.load() == T(0));
	}
	{
		hamon::atomic<T> volatile a(T(13));
		VERIFY(a.load() == T(13));
	}
	{
		hamon::atomic<T> volatile a(T(1));
		a.store(T(2));
		VERIFY(a.load() == T(2));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicIntegralTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<signed char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<signed short>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<signed int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<signed long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<signed long long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<unsigned char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<unsigned short>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<unsigned int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<unsigned long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test<unsigned long long>());

	EXPECT_TRUE(volatile_test<signed char>());
	EXPECT_TRUE(volatile_test<signed short>());
	EXPECT_TRUE(volatile_test<signed int>());
	EXPECT_TRUE(volatile_test<signed long>());
	EXPECT_TRUE(volatile_test<signed long long>());
	EXPECT_TRUE(volatile_test<unsigned char>());
	EXPECT_TRUE(volatile_test<unsigned short>());
	EXPECT_TRUE(volatile_test<unsigned int>());
	EXPECT_TRUE(volatile_test<unsigned long>());
	EXPECT_TRUE(volatile_test<unsigned long long>());
}

}	// namespace atomic_integral_test
}	// namespace hamon_atomic_test
