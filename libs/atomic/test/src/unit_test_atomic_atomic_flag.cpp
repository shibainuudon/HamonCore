/**
 *	@file	unit_test_atomic_atomic_flag.cpp
 *
 *	@brief	atomic_flag のテスト
 */

#include <hamon/atomic/atomic_flag.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_standard_layout.hpp>
#include <hamon/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_flag_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <bool Volatile>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic_flag volatile, hamon::atomic_flag>;

	// [atomics.flag]/3
	// The atomic_flag type is a standard-layout struct. It has a trivial destructor.
	static_assert(hamon::is_standard_layout_v<Atomic>, "");
	static_assert(hamon::is_trivially_destructible_v<Atomic>, "");

	{
		Atomic a;
		VERIFY(a.test() == false);

		bool b1 = a.test_and_set();
		VERIFY(b1 == false);
		VERIFY(a.test() == true);

		bool b2 = a.test_and_set();
		VERIFY(b2 == true);
		VERIFY(a.test() == true);

		a.clear();
		VERIFY(a.test() == false);

		a.clear();
		VERIFY(a.test() == false);
	}
	{
		Atomic a;
		VERIFY(hamon::atomic_flag_test(&a) == false);

		bool b1 = hamon::atomic_flag_test_and_set(&a);
		VERIFY(b1 == false);
		VERIFY(hamon::atomic_flag_test_explicit(&a, hamon::memory_order::seq_cst) == true);

		bool b2 = hamon::atomic_flag_test_and_set_explicit(&a, hamon::memory_order::seq_cst);
		VERIFY(b2 == true);
		VERIFY(hamon::atomic_flag_test(&a) == true);

		hamon::atomic_flag_clear(&a);
		VERIFY(hamon::atomic_flag_test_explicit(&a, hamon::memory_order::seq_cst) == false);

		hamon::atomic_flag_clear_explicit(&a, hamon::memory_order::seq_cst);
		VERIFY(hamon::atomic_flag_test(&a) == false);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	{
		hamon::atomic_flag a;
		a.wait(true);
		a.notify_one();
	}
	{
		hamon::atomic_flag a;
		a.test_and_set();
		a.wait(false, hamon::memory_order::relaxed);
		a.notify_all();
	}
	{
		hamon::atomic_flag a;
		hamon::atomic_flag_test_and_set(&a);
		hamon::atomic_flag_wait(&a, false);
		hamon::atomic_flag_notify_one(&a);
	}
	{
		hamon::atomic_flag a;
		hamon::atomic_flag_wait_explicit(&a, true, hamon::memory_order::relaxed);
		hamon::atomic_flag_notify_all(&a);
	}

	return true;
}

inline bool wait_test()
{
	{
		hamon::atomic_flag volatile a;

		std::thread t1
		{
			[&]()
			{
				a.wait(false);
			}
		};
		std::thread t2
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.test_and_set();
				a.notify_one();
			}
		};

		t1.join();
		t2.join();
	}
	{
		hamon::atomic_flag volatile a{};

		std::thread t1
		{
			[&]()
			{
				a.wait(false, hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				a.wait(false);
			}
		};
		std::thread t3
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.test_and_set();
				a.notify_all();
			}
		};

		t1.join();
		t2.join();
		t3.join();
	}
	{
		hamon::atomic_flag volatile a;

		std::thread t1
		{
			[&]()
			{
				hamon::atomic_flag_wait(&a, false);
			}
		};
		std::thread t2
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				hamon::atomic_flag_test_and_set(&a);
				hamon::atomic_flag_notify_one(&a);
			}
		};

		t1.join();
		t2.join();
	}
	{
		hamon::atomic_flag volatile a{};

		std::thread t1
		{
			[&]()
			{
				hamon::atomic_flag_wait_explicit(&a, false, hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				hamon::atomic_flag_wait(&a, false);
			}
		};
		std::thread t3
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				hamon::atomic_flag_test_and_set(&a);
				hamon::atomic_flag_notify_all(&a);
			}
		};

		t1.join();
		t2.join();
		t3.join();
	}
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicFlagTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false>()));
	EXPECT_TRUE((test<true>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test()));
	EXPECT_TRUE((wait_test()));
}

}	// namespace atomic_flag_test
}	// namespace hamon_atomic_test
