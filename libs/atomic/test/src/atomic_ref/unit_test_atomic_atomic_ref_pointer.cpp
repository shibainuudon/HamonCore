/**
 *	@file	unit_test_atomic_atomic_ref_pointer.cpp
 *
 *	@brief	atomic_ref<pointer-type> のテスト
 */

#include <hamon/atomic/atomic_ref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <thread>

namespace hamon_atomic_test
{
namespace atomic_ref_pointer_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
bool lock_free_test()
{
	T x{0};
	T* p = &x;
	{
		hamon::atomic_ref<T*> a{p};
		if (hamon::atomic_ref<T*>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	{
		hamon::atomic_ref<T*> const a{p};
		if (hamon::atomic_ref<T*>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
		}
	}
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool test()
{
	using AtomicRef   = hamon::atomic_ref<T*>;
	using AtomicCRef  = hamon::atomic_ref<T* const>;
	using AtomicVRef  = hamon::atomic_ref<T* volatile>;
	using AtomicCVRef = hamon::atomic_ref<T* const volatile>;

	static_assert(hamon::is_same_v<T*, typename AtomicRef::value_type>, "");
	static_assert(hamon::is_same_v<T*, typename AtomicCRef::value_type>, "");
	static_assert(hamon::is_same_v<T*, typename AtomicVRef::value_type>, "");
	static_assert(hamon::is_same_v<T*, typename AtomicCVRef::value_type>, "");

	static_assert(hamon::is_same_v<hamon::ptrdiff_t, typename AtomicRef::difference_type>, "");
	static_assert(hamon::is_same_v<hamon::ptrdiff_t, typename AtomicCRef::difference_type>, "");
	static_assert(hamon::is_same_v<hamon::ptrdiff_t, typename AtomicVRef::difference_type>, "");
	static_assert(hamon::is_same_v<hamon::ptrdiff_t, typename AtomicCVRef::difference_type>, "");

	T* p = nullptr;
	{
		AtomicRef a{p};
		VERIFY(a.load() == nullptr);

		AtomicRef a2(a);
		VERIFY(a2.load() == nullptr);

		hamon::atomic_ref<T* const> a3(a2);
		VERIFY(a3.load() == nullptr);

		hamon::atomic_ref<T* volatile> a4(a2);
		VERIFY(a4.load() == nullptr);

		hamon::atomic_ref<T* const volatile> a5(a2);
		VERIFY(a5.load() == nullptr);
	}
	VERIFY(p == nullptr);
	T x{13};
	{
		AtomicRef a{p};
		a.store(&x);
		VERIFY(a.load() == &x);

		AtomicRef a2(a);
		VERIFY(a2.load() == &x);

		hamon::atomic_ref<T* const> a3(a2);
		VERIFY(a3.load() == &x);

		hamon::atomic_ref<T* volatile> a4(a2);
		VERIFY(a4.load() == &x);

		hamon::atomic_ref<T* const volatile> a5(a2);
		VERIFY(a5.load() == &x);
	}
	VERIFY(p == &x);
	{
		AtomicRef a{p};
		T* p2 = (a = nullptr);
		VERIFY(a.load() == nullptr);
		VERIFY(p2 == nullptr);
	}
	VERIFY(p == nullptr);
	{
		AtomicRef a{p};
		VERIFY(a.exchange(&x) == nullptr);
		VERIFY(a.load() == &x);
	}
	VERIFY(p == &x);
	{
		AtomicRef a{p};
		T* p2 = a;
		VERIFY(p2 == &x);
	}
	VERIFY(p == &x);
	T y{42};
	{
		AtomicRef a{p};
		T* expected = &x;
		VERIFY(true == a.compare_exchange_weak(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &x);
	}
	VERIFY(p == &y);
	{
		AtomicRef a{p};
		T* expected = &x;
		VERIFY(false == a.compare_exchange_strong(expected, &y, hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == &y);
		VERIFY(expected == &y);
	}
	VERIFY(p == &y);
	{
		AtomicRef a{p};
		T* expected = &x;
		VERIFY(false == a.compare_exchange_weak(expected, &y));
		VERIFY(a.load() == &y);
		VERIFY(expected == &y);
	}
	VERIFY(p == &y);
	{
		AtomicRef a{p};
		T* expected = &y;
		VERIFY(true == a.compare_exchange_strong(expected, &x));
		VERIFY(a.load() == &x);
		VERIFY(expected == &y);
	}
	VERIFY(p == &x);

	T arr[] = {1,2,3,4,5};
	p = &arr[0];
	{
		AtomicRef a{p};
		T* before = a.fetch_add(2);
		VERIFY(before == &arr[0]);
		VERIFY(a.load() == &arr[2]);
	}
	VERIFY(p == &arr[2]);
	{
		AtomicRef a{p};
		T* before = a.fetch_sub(1);
		VERIFY(before == &arr[2]);
		VERIFY(a.load() == &arr[1]);
	}
	VERIFY(p == &arr[1]);
	{
		AtomicRef a{p};
		T* before = a.fetch_max(&arr[2]);
		VERIFY(before == &arr[1]);
		VERIFY(a.load() == &arr[2]);
	}
	VERIFY(p == &arr[2]);
	{
		AtomicRef a{p};
		T* before = a.fetch_min(&arr[0]);
		VERIFY(before == &arr[2]);
		VERIFY(a.load() == &arr[0]);
	}
	VERIFY(p == &arr[0]);
	{
		AtomicRef a{p};
		a.store_add(3);
		VERIFY(a.load() == &arr[3]);
	}
	VERIFY(p == &arr[3]);
	{
		AtomicRef a{p};
		a.store_sub(2);
		VERIFY(a.load() == &arr[1]);
	}
	VERIFY(p == &arr[1]);
	{
		AtomicRef a{p};
		a.store_max(&arr[3]);
		VERIFY(a.load() == &arr[3]);
	}
	VERIFY(p == &arr[3]);
	{
		AtomicRef a{p};
		a.store_min(&arr[2]);
		VERIFY(a.load() == &arr[2]);
	}
	VERIFY(p == &arr[2]);
	{
		AtomicRef a{p};
		auto t = ++a;
		VERIFY(a.load() == &arr[3]);
		VERIFY(t == &arr[3]);
	}
	VERIFY(p == &arr[3]);
	{
		AtomicRef a{p};
		auto t = --a;
		VERIFY(a.load() == &arr[2]);
		VERIFY(t == &arr[2]);
	}
	VERIFY(p == &arr[2]);
	{
		AtomicRef a{p};
		auto t = a++;
		VERIFY(a.load() == &arr[3]);
		VERIFY(t == &arr[2]);
	}
	VERIFY(p == &arr[3]);
	{
		AtomicRef a{p};
		auto t = a--;
		VERIFY(a.load() == &arr[2]);
		VERIFY(t == &arr[3]);
	}
	VERIFY(p == &arr[2]);
	{
		AtomicRef a{p};
		auto t = a += 2;
		VERIFY(a.load() == &arr[4]);
		VERIFY(t == &arr[4]);
	}
	VERIFY(p == &arr[4]);
	{
		AtomicRef a{p};
		auto t = a -= 3;
		VERIFY(a.load() == &arr[1]);
		VERIFY(t == &arr[1]);
	}
	VERIFY(p == &arr[1]);
	{
		AtomicRef   a1{p};
		AtomicCRef  a2{p};
		AtomicVRef  a3{p};
		AtomicCVRef a4{p};
		VERIFY(a1.address() == &p);
		VERIFY(a2.address() == &p);
		VERIFY(a3.address() == &p);
		VERIFY(a4.address() == &p);
		static_assert(hamon::is_same_v<decltype(a1.address()), void*>, "");
		static_assert(hamon::is_same_v<decltype(a2.address()), void const*>, "");
		static_assert(hamon::is_same_v<decltype(a3.address()), void volatile*>, "");
		static_assert(hamon::is_same_v<decltype(a4.address()), void const volatile*>, "");
	}
	return true;
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool wait_test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicRefPointerTest)
{
	EXPECT_TRUE((lock_free_test<char>()));
	EXPECT_TRUE((lock_free_test<int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_test<int>()));
}

}	// namespace atomic_ref_pointer_test
}	// namespace hamon_atomic_test
