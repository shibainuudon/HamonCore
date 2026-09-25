/**
 *	@file	unit_test_atomic_atomic_integral.cpp
 *
 *	@brief	atomic のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_integral_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
bool lock_free_test()
{
	// [atomics.types.operations]/5
	// [Note 3: The return value of the is_lock_free member function is consistent with
	// the value of is_always_lock_free for the same type. — end note]
	{
		hamon::atomic<T> a;
		if (hamon::atomic<T>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
			VERIFY(hamon::atomic_is_lock_free(&a));
		}
	}
	{
		hamon::atomic<T> volatile a;
		if (hamon::atomic<T>::is_always_lock_free)
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
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<T> volatile, hamon::atomic<T>>;

	static_assert(hamon::is_same_v<T, typename Atomic::value_type>, "");
	static_assert(hamon::is_same_v<T, typename Atomic::difference_type>, "");

	{
		Atomic a;
		VERIFY(a.load() == T(0));
	}
	{
		Atomic a(T(13));
		VERIFY(a.load() == T(13));
	}
	{
		Atomic a(T(1));
		a.store(T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(1));
		T x = (a = T(2));
		VERIFY(a.load() == T(2));
		VERIFY(x == T(2));
	}
	{
		Atomic a(T(3));
		T v = a;
		VERIFY(v == T(3));
	}
	{
		Atomic a(T(1));
		VERIFY(a.exchange(T(4)) == T(1));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == a.compare_exchange_weak(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == a.compare_exchange_weak(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == a.compare_exchange_strong(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == a.compare_exchange_strong(expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == a.compare_exchange_weak(expected, T(2)));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == a.compare_exchange_weak(expected, T(2)));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == a.compare_exchange_strong(expected, T(2)));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == a.compare_exchange_strong(expected, T(2)));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T before = a.fetch_add(T(2));
		VERIFY(before == T(3));
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		T before = a.fetch_sub(T(2));
		VERIFY(before == T(3));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(0x0b));
		T before = a.fetch_and(T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0a));
	}
	{
		Atomic a(T(0x0b));
		T before = a.fetch_or(T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0f));
	}
	{
		Atomic a(T(0x0b));
		T before = a.fetch_xor(T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x05));
	}
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
		Atomic a(T(0x09));
		a.store_and(T(0x05));
		VERIFY(a.load() == T(0x01));
	}
	{
		Atomic a(T(0x09));
		a.store_or(T(0x05));
		VERIFY(a.load() == T(0x0d));
	}
	{
		Atomic a(T(0x09));
		a.store_xor(T(0x05));
		VERIFY(a.load() == T(0x0c));
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
	{
		Atomic a(T(0x0b));
		auto t = a &= T(0x0e);
		VERIFY(a.load() == T(0x0a));
		VERIFY(t == T(0x0a));
	}
	{
		Atomic a(T(0x0b));
		auto t = a |= T(0x0e);
		VERIFY(a.load() == T(0x0f));
		VERIFY(t == T(0x0f));
	}
	{
		Atomic a(T(0x0b));
		auto t = a ^= T(0x0e);
		VERIFY(a.load() == T(0x05));
		VERIFY(t == T(0x05));
	}
	return true;
}

template <bool Volatile, typename T>
HAMON_CXX14_CONSTEXPR bool nonmember_test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<T> volatile, hamon::atomic<T>>;

	{
		Atomic a;
		VERIFY(hamon::atomic_load(&a) == T(0));
	}
	{
		Atomic a(T(13));
		VERIFY(hamon::atomic_load_explicit(&a, hamon::memory_order::seq_cst) == T(13));
	}
	{
		Atomic a(T(1));
		hamon::atomic_store(&a, T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(1));
		hamon::atomic_store_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(1));
		VERIFY(hamon::atomic_exchange(&a, T(4)) == T(1));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(1));
		VERIFY(hamon::atomic_exchange_explicit(&a, T(4), hamon::memory_order::seq_cst) == T(1));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, T(2), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == hamon::atomic_compare_exchange_weak(&a, &expected, T(2)));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == hamon::atomic_compare_exchange_weak(&a, &expected, T(2)));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 3;
		VERIFY(true == hamon::atomic_compare_exchange_strong(&a, &expected, T(2)));
		VERIFY(a.load() == T(2));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T expected = 1;
		VERIFY(false == hamon::atomic_compare_exchange_strong(&a, &expected, T(2)));
		VERIFY(a.load() == T(3));
		VERIFY(expected == T(3));
	}
	{
		Atomic a(T(3));
		T before = hamon::atomic_fetch_add(&a, T(2));
		VERIFY(before == T(3));
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		T before = hamon::atomic_fetch_add_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(before == T(3));
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		T before = hamon::atomic_fetch_sub(&a, T(2));
		VERIFY(before == T(3));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(3));
		T before = hamon::atomic_fetch_sub_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(before == T(3));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_and(&a, T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0a));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_and_explicit(&a, T(0x0e), hamon::memory_order::seq_cst);
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0a));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_or(&a, T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0f));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_or_explicit(&a, T(0x0e), hamon::memory_order::seq_cst);
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x0f));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_xor(&a, T(0x0e));
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x05));
	}
	{
		Atomic a(T(0x0b));
		T before = hamon::atomic_fetch_xor_explicit(&a, T(0x0e), hamon::memory_order::seq_cst);
		VERIFY(before == T(0x0b));
		VERIFY(a.load() == T(0x05));
	}
	{
		Atomic a(T(2));
		T before = hamon::atomic_fetch_max(&a, T(3));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(2));
		T before = hamon::atomic_fetch_max_explicit(&a, T(1), hamon::memory_order::seq_cst);
		VERIFY(before == T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(2));
		T before = hamon::atomic_fetch_min(&a, T(3));
		VERIFY(before == T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(2));
		T before = hamon::atomic_fetch_min_explicit(&a, T(1), hamon::memory_order::seq_cst);
		VERIFY(before == T(2));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_add(&a, T(2));
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_add_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(5));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_sub(&a, T(2));
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_sub_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(1));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_and(&a, T(0x05));
		VERIFY(a.load() == T(0x01));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_and_explicit(&a, T(0x05), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(0x01));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_or(&a, T(0x05));
		VERIFY(a.load() == T(0x0d));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_or_explicit(&a, T(0x05), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(0x0d));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_xor(&a, T(0x05));
		VERIFY(a.load() == T(0x0c));
	}
	{
		Atomic a(T(0x09));
		hamon::atomic_store_xor_explicit(&a, T(0x05), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(0x0c));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_max(&a, T(4));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_max_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_min(&a, T(4));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		hamon::atomic_store_min_explicit(&a, T(2), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(2));
	}
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	//{
	//	hamon::atomic<T> a(T(5));
	//	a.wait(T(5));
	//	a.notify_one();
	//}
	//{
	//	hamon::atomic<T> a(T(6));
	//	a.wait(T(6), hamon::memory_order::relaxed);
	//	a.notify_all();
	//}

	return true;
}

template <typename T>
bool wait_test()
{
	//hamon::atomic<T> a;

	//std::thread t
	//{
	//	[&]()
	//	{
	//		a.store(10);
	//		a.notify_one();
	//	}
	//};

	//a.wait(0);

	//t.join();

	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicIntegralTest)
{
	EXPECT_TRUE((lock_free_test<signed char>()));
	EXPECT_TRUE((lock_free_test<signed short>()));
	EXPECT_TRUE((lock_free_test<signed int>()));
	EXPECT_TRUE((lock_free_test<signed long>()));
	EXPECT_TRUE((lock_free_test<signed long long>()));
	EXPECT_TRUE((lock_free_test<unsigned char>()));
	EXPECT_TRUE((lock_free_test<unsigned short>()));
	EXPECT_TRUE((lock_free_test<unsigned int>()));
	EXPECT_TRUE((lock_free_test<unsigned long>()));
	EXPECT_TRUE((lock_free_test<unsigned long long>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, signed char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, signed short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, signed int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, signed long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, signed long long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, unsigned char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, unsigned short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, unsigned int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, unsigned long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, unsigned long long>()));

	EXPECT_TRUE((test<true, signed char>()));
	EXPECT_TRUE((test<true, signed short>()));
	EXPECT_TRUE((test<true, signed int>()));
	EXPECT_TRUE((test<true, signed long>()));
	EXPECT_TRUE((test<true, signed long long>()));
	EXPECT_TRUE((test<true, unsigned char>()));
	EXPECT_TRUE((test<true, unsigned short>()));
	EXPECT_TRUE((test<true, unsigned int>()));
	EXPECT_TRUE((test<true, unsigned long>()));
	EXPECT_TRUE((test<true, unsigned long long>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, signed char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, signed short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, signed int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, signed long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, signed long long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, unsigned char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, unsigned short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, unsigned int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, unsigned long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, unsigned long long>()));

	EXPECT_TRUE((nonmember_test<true, signed char>()));
	EXPECT_TRUE((nonmember_test<true, signed short>()));
	EXPECT_TRUE((nonmember_test<true, signed int>()));
	EXPECT_TRUE((nonmember_test<true, signed long>()));
	EXPECT_TRUE((nonmember_test<true, signed long long>()));
	EXPECT_TRUE((nonmember_test<true, unsigned char>()));
	EXPECT_TRUE((nonmember_test<true, unsigned short>()));
	EXPECT_TRUE((nonmember_test<true, unsigned int>()));
	EXPECT_TRUE((nonmember_test<true, unsigned long>()));
	EXPECT_TRUE((nonmember_test<true, unsigned long long>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<signed char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<signed short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<signed int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<signed long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<signed long long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<unsigned char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<unsigned short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<unsigned int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<unsigned long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<unsigned long long>()));

	EXPECT_TRUE((wait_test<signed char>()));
	EXPECT_TRUE((wait_test<signed short>()));
	EXPECT_TRUE((wait_test<signed int>()));
	EXPECT_TRUE((wait_test<signed long>()));
	EXPECT_TRUE((wait_test<signed long long>()));
	EXPECT_TRUE((wait_test<unsigned char>()));
	EXPECT_TRUE((wait_test<unsigned short>()));
	EXPECT_TRUE((wait_test<unsigned int>()));
	EXPECT_TRUE((wait_test<unsigned long>()));
	EXPECT_TRUE((wait_test<unsigned long long>()));

	{
		hamon::atomic<int> x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x++;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x++;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(2000, x);
	}
	{
		hamon::atomic<int> x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x--;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x--;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(-2000, x);
	}
	{
		hamon::atomic<int> x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x += 3;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x -= 2;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(1000, x);
	}
	{
		hamon::atomic<int> x{0b1111};
		std::thread t1{[&x]() { x &= 0b0111; }};
		std::thread t2{[&x]() { x &= 0b0101; }};
		t1.join();
		t2.join();
		EXPECT_EQ(0b0101, x);
	}
	{
		hamon::atomic<int> x{0b0110};
		std::thread t1{[&x]() { x |= 0b0001; }};
		std::thread t2{[&x]() { x |= 0b1000; }};
		t1.join();
		t2.join();
		EXPECT_EQ(0b1111, x);
	}
	{
		hamon::atomic<int> x{0b1111};
		std::thread t1{[&x]() { x ^= 0b1011; }};
		std::thread t2{[&x]() { x ^= 0b0101; }};
		t1.join();
		t2.join();
		EXPECT_EQ(0b0001, x);
	}
}

}	// namespace atomic_integral_test
}	// namespace hamon_atomic_test
