/**
 *	@file	unit_test_atomic_atomic_ref_bool.cpp
 *
 *	@brief	atomic_ref<bool> のテスト
 */

#include <hamon/atomic/atomic_ref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_ref_bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline bool lock_free_test()
{
	bool b = false;
	{
		hamon::atomic_ref<bool> a(b);
		if (hamon::atomic_ref<bool>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	{
		hamon::atomic_ref<bool> const a(b);
		if (hamon::atomic_ref<bool>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool test()
{
	using AtomicRef   = hamon::atomic_ref<bool>;
	using AtomicCRef  = hamon::atomic_ref<bool const>;
	using AtomicVRef  = hamon::atomic_ref<bool volatile>;
	using AtomicCVRef = hamon::atomic_ref<bool const volatile>;

	static_assert(hamon::is_same_v<bool, typename AtomicRef::value_type>, "");
	static_assert(hamon::is_same_v<bool, typename AtomicCRef::value_type>, "");
	static_assert(hamon::is_same_v<bool, typename AtomicVRef::value_type>, "");
	static_assert(hamon::is_same_v<bool, typename AtomicCVRef::value_type>, "");

	bool b = false;
	{
		AtomicRef a{b};
		VERIFY(a.load() == false);

		AtomicRef a2(a);
		VERIFY(a2.load() == false);

		AtomicCRef a3(a2);
		VERIFY(a3.load() == false);

		AtomicVRef a4(a2);
		VERIFY(a4.load() == false);

		AtomicCVRef a5(a2);
		VERIFY(a5.load() == false);
	}
	VERIFY(b == false);
	{
		AtomicRef a{b};
		a.store(true);
		VERIFY(a.load() == true);
	}
	VERIFY(b == true);
	{
		AtomicRef a{b};
		bool x = (a = false);
		VERIFY(a.load() == false);
		VERIFY(x == false);
	}
	VERIFY(b == false);
	{
		AtomicRef a{b};
		bool v = a;
		VERIFY(v == false);
	}
	VERIFY(b == false);
	{
		AtomicRef a{b};
		VERIFY(a.exchange(true) == false);
		VERIFY(a.load() == true);
	}
	VERIFY(b == true);
	{
		AtomicRef a{b};
		bool expected = true;
		VERIFY(true == a.compare_exchange_weak(expected, false, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == false);
		VERIFY(expected == true);
	}
	VERIFY(b == false);
	{
		AtomicRef a{b};
		bool expected = true;
		VERIFY(false == a.compare_exchange_strong(expected, true, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == false);
		VERIFY(expected == false);
	}
	VERIFY(b == false);
	{
		AtomicRef a{b};
		bool expected = false;
		VERIFY(true == a.compare_exchange_weak(expected, true));
		VERIFY(a.load() == true);
		VERIFY(expected == false);
	}
	VERIFY(b == true);
	{
		AtomicRef a{b};
		bool expected = false;
		VERIFY(false == a.compare_exchange_strong(expected, true));
		VERIFY(a.load() == true);
		VERIFY(expected == true);
	}
	VERIFY(b == true);
	{
		AtomicRef   a1{b};
		AtomicCRef  a2{b};
		AtomicVRef  a3{b};
		AtomicCVRef a4{b};
		VERIFY(a1.address() == &b);
		VERIFY(a2.address() == &b);
		VERIFY(a3.address() == &b);
		VERIFY(a4.address() == &b);
		static_assert(hamon::is_same_v<decltype(a1.address()), void*>, "");
		static_assert(hamon::is_same_v<decltype(a2.address()), void const*>, "");
		static_assert(hamon::is_same_v<decltype(a3.address()), void volatile*>, "");
		static_assert(hamon::is_same_v<decltype(a4.address()), void const volatile*>, "");
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	{
		bool x = true;
		hamon::atomic_ref<bool> a(x);
		a.wait(false);
		a.notify_one();
	}
	{
		bool x = false;
		hamon::atomic_ref<bool> a(x);
		a.wait(true, hamon::memory_order::relaxed);
		a.notify_all();
	}

	return true;
}

inline bool wait_test()
{
	{
		bool x = false;
		hamon::atomic_ref<bool> a{x};

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
				a.store(true);
				a.notify_one();
			}
		};

		t1.join();
		t2.join();
	}
	{
		bool x = true;
		hamon::atomic_ref<bool> a{x};

		std::thread t1
		{
			[&]()
			{
				a.wait(true, hamon::memory_order::relaxed);
			}
		};
		std::thread t2
		{
			[&]()
			{
				a.wait(true);
			}
		};
		std::thread t3
		{
			[&]()
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds{1});
				a.store(false);
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

GTEST_TEST(AtomicTest, AtomicRefBoolTest)
{
	EXPECT_TRUE((lock_free_test()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test()));

	EXPECT_TRUE((wait_test()));
}

}	// namespace atomic_ref_bool_test
}	// namespace hamon_atomic_test
