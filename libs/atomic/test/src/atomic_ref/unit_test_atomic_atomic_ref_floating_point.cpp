/**
 *	@file	unit_test_atomic_ref_atomic_floating_point.cpp
 *
 *	@brief	atomic_ref<floating-point-type> のテスト
 */

#include <hamon/atomic/atomic_ref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_ref_floating_point_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
bool lock_free_test()
{
	T x = 0;
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

	T x = T(0.5);
	{
		AtomicRef a{x};
		VERIFY(a.load() == T(0.5));

		AtomicRef a2(a);
		VERIFY(a2.load() == T(0.5));

		AtomicCRef a3(a2);
		VERIFY(a3.load() == T(0.5));

		AtomicVRef a4(a2);
		VERIFY(a4.load() == T(0.5));

		AtomicCVRef a5(a2);
		VERIFY(a5.load() == T(0.5));
	}
	VERIFY(x == T(0.5));
	{
		AtomicRef a{x};
		a.store(T(1.5));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		T t = (a = T(-2.5));
		VERIFY(a.load() == T(-2.5));
		VERIFY(t == T(-2.5));
	}
	VERIFY(x == T(-2.5));
	{
		AtomicRef a{x};
		T v = a;
		VERIFY(v == T(-2.5));
	}
	VERIFY(x == T(-2.5));
	{
		AtomicRef a{x};
		VERIFY(a.exchange(T(4.5)) == T(-2.5));
		VERIFY(a.load() == T(4.5));
	}
	VERIFY(x == T(4.5));
	{
		AtomicRef a{x};
		T expected = 4.5;
		VERIFY(true == a.compare_exchange_weak(expected, T(3.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.0));
		VERIFY(expected == T(4.5));
	}
	VERIFY(x == T(3.0));
	{
		AtomicRef a{x};
		T expected = 3.5;
		VERIFY(false == a.compare_exchange_strong(expected, T(4.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.0));
		VERIFY(expected == T(3.0));
	}
	VERIFY(x == T(3.0));
	{
		AtomicRef a{x};
		T expected = 3.5;
		VERIFY(false == a.compare_exchange_weak(expected, T(2.0)));
		VERIFY(a.load() == T(3.0));
		VERIFY(expected == T(3.0));
	}
	VERIFY(x == T(3.0));
	{
		AtomicRef a{x};
		T expected = 3.0;
		VERIFY(true == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(expected == T(3.0));
	}
	VERIFY(x == T(2.5));
	{
		AtomicRef a{x};
		T before = a.fetch_add(T(0.5));
		VERIFY(before == T(2.5));
		VERIFY(a.load() == T(3.0));
	}
	VERIFY(x == T(3.0));
	{
		AtomicRef a{x};
		T before = a.fetch_sub(T(1.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		T before = a.fetch_max(T(-2.5));
		VERIFY(before == T(1.5));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		T before = a.fetch_min(T(-2.5));
		VERIFY(before == T(1.5));
		VERIFY(a.load() == T(-2.5));
	}
	VERIFY(x == T(-2.5));
	{
		AtomicRef a{x};
		T before = a.fetch_fmaximum(T(1.0));
		VERIFY(before == T(-2.5));
		VERIFY(a.load() == T(1.0));
	}
	VERIFY(x == T(1.0));
	{
		AtomicRef a{x};
		T before = a.fetch_fminimum(T(1.0));
		VERIFY(before == T(1.0));
		VERIFY(a.load() == T(1.0));
	}
	VERIFY(x == T(1.0));
	{
		AtomicRef a{x};
		T before = a.fetch_fmaximum_num(T(1.5));
		VERIFY(before == T(1.0));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		T before = a.fetch_fminimum_num(T(0.5));
		VERIFY(before == T(1.5));
		VERIFY(a.load() == T(0.5));
	}
	VERIFY(x == T(0.5));
	{
		AtomicRef a{x};
		a.store_add(T(1.0));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		a.store_sub(T(0.5));
		VERIFY(a.load() == T(1.0));
	}
	VERIFY(x == T(1.0));
	{
		AtomicRef a{x};
		a.store_max(T(2.0));
		VERIFY(a.load() == T(2.0));
	}
	VERIFY(x == T(2.0));
	{
		AtomicRef a{x};
		a.store_min(T(1.5));
		VERIFY(a.load() == T(1.5));
	}
	VERIFY(x == T(1.5));
	{
		AtomicRef a{x};
		a.store_fmaximum(T(2.5));
		VERIFY(a.load() == T(2.5));
	}
	VERIFY(x == T(2.5));
	{
		AtomicRef a{x};
		a.store_fminimum(T(-1.5));
		VERIFY(a.load() == T(-1.5));
	}
	VERIFY(x == T(-1.5));
	{
		AtomicRef a{x};
		a.store_fmaximum_num(T(4.0));
		VERIFY(a.load() == T(4.0));
	}
	VERIFY(x == T(4.0));
	{
		AtomicRef a{x};
		a.store_fminimum_num(T(3.5));
		VERIFY(a.load() == T(3.5));
	}
	VERIFY(x == T(3.5));
	{
		AtomicRef a{x};
		auto t = a += T(2.5);
		VERIFY(a.load() == T(6.0));
		VERIFY(t == T(6.0));
	}
	VERIFY(x == T(6.0));
	{
		AtomicRef a{x};
		auto t = a -= T(1.5);
		VERIFY(a.load() == T(4.5));
		VERIFY(t == T(4.5));
	}
	VERIFY(x == T(4.5));
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
		T x = 1;
		hamon::atomic_ref<T> a(x);
		a.wait(T(2));
		a.notify_one();
	}
	{
		T x = 3;
		hamon::atomic_ref<T> a(x);
		a.wait(T(4), hamon::memory_order::relaxed);
		a.notify_all();
	}

	return true;
}

template <typename T>
inline bool wait_test()
{
	{
		T x = T(0.5);
		hamon::atomic_ref<T> a{x};

		std::thread t1
		{
			[&]()
			{
				a.wait(T(0.5));
			}
		};
		std::thread t2
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.store(T(1.5));
				a.notify_one();
			}
		};

		t1.join();
		t2.join();
	}
	{
		T x = T(2.5);
		hamon::atomic_ref<T> a{x};

		std::thread t1
		{
			[&]()
			{
				a.wait(T(2.5), hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				a.wait(T(2.5));
			}
		};
		std::thread t3
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.store(T(3.5));
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

GTEST_TEST(AtomicTest, AtomicRefFloatingPointTest)
{
	EXPECT_TRUE((lock_free_test<float>()));
	EXPECT_TRUE((lock_free_test<double>()));
	//EXPECT_TRUE((lock_free_test<long double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<long double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<long double>()));

	EXPECT_TRUE((wait_test<float>()));
	EXPECT_TRUE((wait_test<double>()));
	//EXPECT_TRUE((wait_test<long double>()));

	{
		float x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<float> a{x};
					a += 0.5;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					hamon::atomic_ref<float> a{x};
					a -= 1.5;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(-1000, x);
	}
}

}	// namespace atomic_ref_floating_point_test
}	// namespace hamon_atomic_test
