/**
 *	@file	unit_test_atomic_atomic_bool.cpp
 *
 *	@brief	atomic<bool> のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <thread>

namespace hamon_atomic_test
{
namespace atomic_bool_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline bool lock_free_test()
{
	// [atomics.types.operations]/5
	// [Note 3: The return value of the is_lock_free member function is consistent with
	// the value of is_always_lock_free for the same type. — end note]
	{
		hamon::atomic<bool> a;
		if (hamon::atomic<bool>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	{
		hamon::atomic<bool> volatile a;
		if (hamon::atomic<bool>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	return true;
}

template <bool Volatile>
HAMON_CXX14_CONSTEXPR bool test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<bool> volatile, hamon::atomic<bool>>;

	static_assert(hamon::is_same_v<bool, typename Atomic::value_type>, "");

	{
		Atomic a;
		VERIFY(a.load() == false);
	}
	{
		Atomic a(true);
		VERIFY(a.load() == true);
	}
	{
		Atomic a(false);
		a.store(true);
		VERIFY(a.load() == true);
	}
	{
		Atomic a(true);
		bool x = (a = false);
		VERIFY(a.load() == false);
		VERIFY(x == false);
	}
	{
		Atomic a(false);
		bool v = a;
		VERIFY(v == false);
	}
	{
		Atomic a(true);
		VERIFY(a.exchange(false) == true);
		VERIFY(a.load() == false);
	}
	{
		Atomic a(false);
		bool expected = false;
		VERIFY(true == a.compare_exchange_weak(expected, true, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == true);
		VERIFY(expected == false);
	}
	{
		Atomic a(false);
		bool expected = true;
		VERIFY(false == a.compare_exchange_weak(expected, true, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == false);
		VERIFY(expected == false);
	}
	{
		Atomic a(true);
		bool expected = true;
		VERIFY(true == a.compare_exchange_strong(expected, false, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == false);
		VERIFY(expected == true);
	}
	{
		Atomic a(true);
		bool expected = false;
		VERIFY(false == a.compare_exchange_strong(expected, true, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == true);
		VERIFY(expected == true);
	}
	{
		Atomic a(false);
		bool expected = false;
		VERIFY(true == a.compare_exchange_weak(expected, false));
		VERIFY(a.load() == false);
		VERIFY(expected == false);
	}
	{
		Atomic a(false);
		bool expected = true;
		VERIFY(false == a.compare_exchange_weak(expected, false));
		VERIFY(a.load() == false);
		VERIFY(expected == false);
	}
	{
		Atomic a(true);
		bool expected = true;
		VERIFY(true == a.compare_exchange_strong(expected, false));
		VERIFY(a.load() == false);
		VERIFY(expected == true);
	}
	{
		Atomic a(true);
		bool expected = false;
		VERIFY(false == a.compare_exchange_strong(expected, false));
		VERIFY(a.load() == true);
		VERIFY(expected == true);
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool wait_constexpr_test()
{
	return true;
}

inline bool wait_test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicBoolTest)
{
	EXPECT_TRUE((lock_free_test()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false>()));

	EXPECT_TRUE((test<true>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test()));

	EXPECT_TRUE((wait_test()));
}

}	// namespace atomic_bool_test
}	// namespace hamon_atomic_test
