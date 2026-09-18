/**
 *	@file	unit_test_atomic_atomic_pointer.cpp
 *
 *	@brief	atomic のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <thread>

namespace hamon_atomic_test
{
namespace atomic_pointer_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
bool lock_free_test()
{
	// [atomics.types.operations]/5
	// [Note 3: The return value of the is_lock_free member function is consistent with
	// the value of is_always_lock_free for the same type. — end note]
	{
		hamon::atomic<T*> a;
		if (hamon::atomic<T*>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	{
		hamon::atomic<T*> volatile a;
		if (hamon::atomic<T*>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	return true;
}

template <bool Volatile, typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<T*> volatile, hamon::atomic<T*>>;

	static_assert(hamon::is_same_v<T*, typename Atomic::value_type>, "");
	static_assert(hamon::is_same_v<hamon::ptrdiff_t, typename Atomic::difference_type>, "");

	{
		Atomic a;
		VERIFY(a.load() == nullptr);
	}
	{
		T x = 13;
		Atomic a(&x);
		VERIFY(a.load() == &x);
	}
	{
		Atomic a(nullptr);
		T x = 2;
		a.store(&x);
		VERIFY(a.load() == &x);
	}
	{
		T x = 3;
		Atomic a(&x);
		T* y = (a = nullptr);
		VERIFY(a.load() == nullptr);
		VERIFY(y == nullptr);
	}
	{
		T x = 4;
		Atomic a(&x);
		T* y = a;
		VERIFY(y == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		VERIFY(a.exchange(&y) == &x);
		VERIFY(a.load() == &y);
	}
	//{
	//	T x = 1;
	//	T y = 2;
	//	//T z = 3;
	//	Atomic a(&x);
	//	T* expected = &x;
	//	VERIFY(true == a.compare_exchange_weak(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
	//	VERIFY(a.load() == &x);
	//	VERIFY(expected == &x);
	//}
	//{
	//	Atomic a(T(3));
	//	T expected = 1;
	//	VERIFY(false == a.compare_exchange_weak(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
	//	VERIFY(a.load() == T(3));
	//	VERIFY(expected == T(3));
	//}
	//{
	//	Atomic a(T(3));
	//	T expected = 3;
	//	VERIFY(true == a.compare_exchange_strong(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
	//	VERIFY(a.load() == T(2));
	//	VERIFY(expected == T(3));
	//}
	//{
	//	Atomic a(T(3));
	//	T expected = 1;
	//	VERIFY(false == a.compare_exchange_strong(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
	//	VERIFY(a.load() == T(3));
	//	VERIFY(expected == T(3));
	//}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == a.compare_exchange_weak(expected, &y));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == a.compare_exchange_weak(expected, &y));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == a.compare_exchange_strong(expected, &y));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == a.compare_exchange_strong(expected, &y));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		T* before = a.fetch_add(2);
		VERIFY(before == &arr[0]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[2]);
		T* before = a.fetch_add(-1);
		VERIFY(before == &arr[2]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = a.fetch_sub(1);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		T* before = a.fetch_sub(-2);
		VERIFY(before == &arr[0]);
		VERIFY(a.load() == &arr[2]);
	}
#if 0
	{
		Atomic a(T(2));
		T before = a.fetch_max(T(3));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(2));
		T before = a.fetch_max(T(1));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(2));
		T before = a.fetch_min(T(3));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(2));
		T before = a.fetch_min(T(1));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(3));
		a.store_add(T(2));
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		a.store_sub(T(2));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(3));
		a.store_max(T(4));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		a.store_max(T(2));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		a.store_min(T(4));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		a.store_min(T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(3));
		auto t = ++a;
		VERIFY(a.load() == T(4));
		VERIFY(t == T(4));
	}
	{
		Atomic a(T(3));
		auto t = --a;
		VERIFY(a.load() == T(2));
		VERIFY(t == T(2));
	}
	{
		Atomic a(T(3));
		auto t = a++;
		VERIFY(a.load() == T(4));
		VERIFY(t == T(3));
	}
	{
		Atomic a(T(3));
		auto t = a--;
		VERIFY(a.load() == T(2));
		VERIFY(t == T(3));
	}
	{
		Atomic a(T(3));
		auto t = a += T(2);
		VERIFY(a.load() == T(5));
		VERIFY(t == T(5));
	}
	{
		Atomic a(T(3));
		auto t = a -= T(2);
		VERIFY(a.load() == T(1));
		VERIFY(t == T(1));
	}
#endif
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	return true;
}

template <typename T>
bool wait_test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicPointerTest)
{
	EXPECT_TRUE((lock_free_test<int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, int>()));

	EXPECT_TRUE((test<true, char>()));
	EXPECT_TRUE((test<true, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<int>()));

	EXPECT_TRUE((wait_test<int>()));
}

}	// namespace atomic_pointer_test
}	// namespace hamon_atomic_test
