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
			VERIFY(hamon::atomic_is_lock_free(&a));
		}
	}
	{
		hamon::atomic<T*> volatile a;
		if (hamon::atomic<T*>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
			VERIFY(hamon::atomic_is_lock_free(&a));
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
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == a.compare_exchange_weak(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == a.compare_exchange_weak(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == a.compare_exchange_strong(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == a.compare_exchange_strong(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
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
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = a.fetch_max(&arr[2]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = a.fetch_max(&arr[0]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = a.fetch_min(&arr[2]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = a.fetch_min(&arr[0]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		a.store_add(2);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		a.store_sub(1);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		a.store_max(&arr[2]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		a.store_max(&arr[0]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		a.store_min(&arr[2]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		a.store_min(&arr[0]);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		auto t = ++a;
		VERIFY(a.load() == &arr[2]);
		VERIFY(t == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		auto t = --a;
		VERIFY(a.load() == &arr[0]);
		VERIFY(t == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		auto t = a++;
		VERIFY(a.load() == &arr[2]);
		VERIFY(t == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		auto t = a--;
		VERIFY(a.load() == &arr[0]);
		VERIFY(t == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		auto t = a += 2;
		VERIFY(a.load() == &arr[2]);
		VERIFY(t == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[2]);
		auto t = a -= 2;
		VERIFY(a.load() == &arr[0]);
		VERIFY(t == &arr[0]);
	}
	return true;
}

template <bool Volatile, typename T>
HAMON_CXX14_CONSTEXPR bool nonmember_test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<T*> volatile, hamon::atomic<T*>>;

	{
		Atomic a;
		VERIFY(hamon::atomic_load(&a) == nullptr);
	}
	{
		T x = 13;
		Atomic a(&x);
		VERIFY(hamon::atomic_load_explicit(&a, hamon::memory_order::seq_cst) == &x);
	}
	{
		Atomic a(nullptr);
		T x = 2;
		hamon::atomic_store(&a, &x);
		VERIFY(a.load() == &x);
	}
	{
		Atomic a(nullptr);
		T x = 2;
		hamon::atomic_store_explicit(&a, &x, hamon::memory_order::seq_cst);
		VERIFY(a.load() == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		VERIFY(hamon::atomic_exchange(&a, &y) == &x);
		VERIFY(a.load() == &y);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		VERIFY(hamon::atomic_exchange_explicit(&a, &y, hamon::memory_order::seq_cst) == &x);
		VERIFY(a.load() == &y);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == hamon::atomic_compare_exchange_weak(&a, &expected, &y));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == hamon::atomic_compare_exchange_weak(&a, &expected, &y));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		Atomic a(&x);
		T* expected = &x;
		VERIFY(true == hamon::atomic_compare_exchange_strong(&a, &expected, &y));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	{
		T x = 1;
		T y = 2;
		T z = 3;
		Atomic a(&x);
		T* expected = &z;
		VERIFY(false == hamon::atomic_compare_exchange_strong(&a, &expected, &y));
		VERIFY(a.load() == &x);
		VERIFY(expected == &x);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		T* before = hamon::atomic_fetch_add(&a, 2);
		VERIFY(before == &arr[0]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[2]);
		T* before = hamon::atomic_fetch_add_explicit(&a, -1, hamon::memory_order::seq_cst);
		VERIFY(before == &arr[2]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = hamon::atomic_fetch_sub(&a, 1);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		T* before = hamon::atomic_fetch_sub_explicit(&a, -2, hamon::memory_order::seq_cst);
		VERIFY(before == &arr[0]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = hamon::atomic_fetch_max(&a, &arr[2]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = hamon::atomic_fetch_max_explicit(&a, &arr[0], hamon::memory_order::seq_cst);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = hamon::atomic_fetch_min(&a, &arr[2]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		T* before = hamon::atomic_fetch_min_explicit(&a, &arr[0], hamon::memory_order::seq_cst);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		hamon::atomic_store_add(&a, 2);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[0]);
		hamon::atomic_store_add_explicit(&a, 2, hamon::memory_order::seq_cst);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_sub(&a, 1);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_sub_explicit(&a, 1, hamon::memory_order::seq_cst);
		VERIFY(a.load() == &arr[0]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_max(&a, &arr[2]);
		VERIFY(a.load() == &arr[2]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_max_explicit(&a, &arr[0], hamon::memory_order::seq_cst);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_min(&a, &arr[2]);
		VERIFY(a.load() == &arr[1]);
	}
	{
		T arr[] = {1,2,3};
		Atomic a(&arr[1]);
		hamon::atomic_store_min_explicit(&a, &arr[0], hamon::memory_order::seq_cst);
		VERIFY(a.load() == &arr[0]);
	}
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
	EXPECT_TRUE((lock_free_test<char>()));
	EXPECT_TRUE((lock_free_test<int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, int>()));

	EXPECT_TRUE((test<true, char>()));
	EXPECT_TRUE((test<true, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, int>()));

	EXPECT_TRUE((nonmember_test<true, char>()));
	EXPECT_TRUE((nonmember_test<true, int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<int>()));

	EXPECT_TRUE((wait_test<char>()));
	EXPECT_TRUE((wait_test<int>()));
}

}	// namespace atomic_pointer_test
}	// namespace hamon_atomic_test
