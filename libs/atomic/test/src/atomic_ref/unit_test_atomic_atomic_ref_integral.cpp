/**
 *	@file	unit_test_atomic_atomic_ref_integral.cpp
 *
 *	@brief	atomic_ref<integral-type> のテスト
 */

#include <hamon/atomic/atomic_ref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_ref_integral_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
bool lock_free_test()
{
	T x = 13;
	{
		hamon::atomic_ref<T> a{x};
		if (hamon::atomic_ref<T>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	{
		hamon::atomic_ref<T> const a{x};
		if (hamon::atomic_ref<T>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	using AtomicRef   = hamon::atomic_ref<T>;
	using AtomicCRef  = hamon::atomic_ref<T const>;
	using AtomicVRef  = hamon::atomic_ref<T volatile>;
	using AtomicCVRef = hamon::atomic_ref<T const volatile>;

	static_assert(hamon::is_same_v<T, typename AtomicRef::value_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicCRef::value_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicVRef::value_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicCVRef::value_type>, "");

	static_assert(hamon::is_same_v<T, typename AtomicRef::difference_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicCRef::difference_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicVRef::difference_type>, "");
	static_assert(hamon::is_same_v<T, typename AtomicCVRef::difference_type>, "");

	T x = 13;
	{
		AtomicRef a{x};
		VERIFY(a.load() == T(13));

		AtomicRef a2(a);
		VERIFY(a2.load() == T(13));

		hamon::atomic_ref<T const> a3(a2);
		VERIFY(a3.load() == T(13));

		hamon::atomic_ref<T volatile> a4(a2);
		VERIFY(a4.load() == T(13));

		hamon::atomic_ref<T const volatile> a5(a2);
		VERIFY(a5.load() == T(13));
	}
	VERIFY(x == T(13));
	{
		AtomicRef a{x};
		a.store(T(10));
		VERIFY(a.load() == T(10));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		T t = (a = T(42));
		VERIFY(a.load() == T(42));
		VERIFY(t == T(42));
	}
	VERIFY(x == T(42));
	{
		AtomicRef a{x};
		T v = a;
		VERIFY(v == T(42));
	}
	VERIFY(x == T(42));
	{
		AtomicRef a{x};
		VERIFY(a.exchange(T(20)) == T(42));
		VERIFY(a.load() == T(20));
	}
	VERIFY(x == T(20));
	{
		AtomicRef a{x};
		T expected = 20;
		VERIFY(true == a.compare_exchange_weak(expected, T(30), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(30));
		VERIFY(expected == T(20));
	}
	VERIFY(x == T(30));
	{
		AtomicRef a{x};
		T expected = 31;
		VERIFY(false == a.compare_exchange_strong(expected, T(21), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(30));
		VERIFY(expected == T(30));
	}
	VERIFY(x == T(30));
	{
		AtomicRef a{x};
		T expected = 40;
		VERIFY(false == a.compare_exchange_weak(expected, T(10)));
		VERIFY(a.load() == T(30));
		VERIFY(expected == T(30));
	}
	VERIFY(x == T(30));
	{
		AtomicRef a{x};
		T expected = 30;
		VERIFY(true == a.compare_exchange_strong(expected, T(10)));
		VERIFY(a.load() == T(10));
		VERIFY(expected == T(30));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		T before = a.fetch_add(T(1));
		VERIFY(before == T(10));
		VERIFY(a.load() == T(11));
	}
	VERIFY(x == T(11));
	{
		AtomicRef a{x};
		T before = a.fetch_sub(T(2));
		VERIFY(before == T(11));
		VERIFY(a.load() == T(9));
	}
	VERIFY(x == T(9));
	{
		AtomicRef a{x};
		T before = a.fetch_and(T(8));
		VERIFY(before == T(9));
		VERIFY(a.load() == T(8));
	}
	VERIFY(x == T(8));
	{
		AtomicRef a{x};
		T before = a.fetch_or(T(12));
		VERIFY(before == T(8));
		VERIFY(a.load() == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		T before = a.fetch_xor(T(7));
		VERIFY(before == T(12));
		VERIFY(a.load() == T(11));
	}
	VERIFY(x == T(11));
	{
		AtomicRef a{x};
		T before = a.fetch_max(T(12));
		VERIFY(before == T(11));
		VERIFY(a.load() == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		T before = a.fetch_max(T(10));
		VERIFY(before == T(12));
		VERIFY(a.load() == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		T before = a.fetch_min(T(13));
		VERIFY(before == T(12));
		VERIFY(a.load() == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		T before = a.fetch_min(T(10));
		VERIFY(before == T(12));
		VERIFY(a.load() == T(10));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		a.store_add(T(-2));
		VERIFY(a.load() == T(8));
	}
	VERIFY(x == T(8));
	{
		AtomicRef a{x};
		a.store_sub(T(-3));
		VERIFY(a.load() == T(11));
	}
	VERIFY(x == T(11));
	{
		AtomicRef a{x};
		a.store_and(T(14));
		VERIFY(a.load() == T(10));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		a.store_or(T(1));
		VERIFY(a.load() == T(11));
	}
	VERIFY(x == T(11));
	{
		AtomicRef a{x};
		a.store_xor(T(6));
		VERIFY(a.load() == T(13));
	}
	VERIFY(x == T(13));
	{
		AtomicRef a{x};
		a.store_max(T(14));
		VERIFY(a.load() == T(14));
	}
	VERIFY(x == T(14));
	{
		AtomicRef a{x};
		a.store_min(T(12));
		VERIFY(a.load() == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		auto t = ++a;
		VERIFY(a.load() == T(13));
		VERIFY(t == T(13));
	}
	VERIFY(x == T(13));
	{
		AtomicRef a{x};
		auto t = --a;
		VERIFY(a.load() == T(12));
		VERIFY(t == T(12));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		auto t = a++;
		VERIFY(a.load() == T(13));
		VERIFY(t == T(12));
	}
	VERIFY(x == T(13));
	{
		AtomicRef a{x};
		auto t = a--;
		VERIFY(a.load() == T(12));
		VERIFY(t == T(13));
	}
	VERIFY(x == T(12));
	{
		AtomicRef a{x};
		auto t = a += T(2);
		VERIFY(a.load() == T(14));
		VERIFY(t == T(14));
	}
	VERIFY(x == T(14));
	{
		AtomicRef a{x};
		auto t = a -= T(4);
		VERIFY(a.load() == T(10));
		VERIFY(t == T(10));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		auto t = a &= T(12);
		VERIFY(a.load() == T(8));
		VERIFY(t == T(8));
	}
	VERIFY(x == T(8));
	{
		AtomicRef a{x};
		auto t = a |= T(10);
		VERIFY(a.load() == T(10));
		VERIFY(t == T(10));
	}
	VERIFY(x == T(10));
	{
		AtomicRef a{x};
		auto t = a ^= T(3);
		VERIFY(a.load() == T(9));
		VERIFY(t == T(9));
	}
	VERIFY(x == T(9));
	{
		AtomicRef   a1{x};
		AtomicCRef  a2{x};
		AtomicVRef  a3{x};
		AtomicCVRef a4{x};
		VERIFY(a1.address() == &x);
		VERIFY(a2.address() == &x);
		VERIFY(a3.address() == &x);
		VERIFY(a4.address() == &x);
		static_assert(hamon::is_same_v<decltype(a1.address()), void*>, "");
		static_assert(hamon::is_same_v<decltype(a2.address()), void const*>, "");
		static_assert(hamon::is_same_v<decltype(a3.address()), void volatile*>, "");
		static_assert(hamon::is_same_v<decltype(a4.address()), void const volatile*>, "");
	}
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	{
		T x = 0;
		hamon::atomic_ref<T> a(x);
		a.wait(T(1));
		a.notify_one();
	}
	{
		T x = 1;
		hamon::atomic_ref<T> a(x);
		a.wait(T(0), hamon::memory_order::relaxed);
		a.notify_all();
	}
	return true;
}

template <typename T>
inline bool wait_test()
{
	{
		T x = 0;
		hamon::atomic_ref<T> a{x};

		std::thread t1
		{
			[&]()
			{
				a.wait(0);
			}
		};
		std::thread t2
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.store(1);
				a.notify_one();
			}
		};

		t1.join();
		t2.join();
	}
	{
		T x = 10;
		hamon::atomic_ref<T> a{x};

		std::thread t1
		{
			[&]()
			{
				a.wait(10, hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				a.wait(10);
			}
		};
		std::thread t3
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.store(20);
				a.notify_all();
			}
		};

		t1.join();
		t2.join();
		t3.join();
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicRefIntegralTest)
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

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<signed char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<signed short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<signed int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<signed long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<signed long long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<unsigned char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<unsigned short>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<unsigned int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<unsigned long>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<unsigned long long>()));

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
		int x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					a++;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					++a;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(2000, x);
	}
	{
		int x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					a--;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					--a;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(-2000, x);
	}
	{
		int x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					a += 3;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<int> a{x};
					a -= 2;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(1000, x);
	}
}

}	// namespace atomic_ref_integral_test
}	// namespace hamon_atomic_test
