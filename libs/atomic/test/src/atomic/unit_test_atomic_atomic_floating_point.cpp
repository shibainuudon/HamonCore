/**
 *	@file	unit_test_atomic_atomic_floating_point.cpp
 *
 *	@brief	atomic<floating-point-type> のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/cmath.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#include <thread>

namespace hamon_atomic_test
{
namespace atomic_floating_point_test
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

	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();

	{
		Atomic a;
		VERIFY(a.load() == T(0));
	}
	{
		Atomic a(T(2.5));
		VERIFY(a.load() == T(2.5));
	}
	{
		Atomic a(T(1));
		a.store(T(-2.5));
		VERIFY(a.load() == T(-2.5));
	}
	{
		Atomic a(T(1));
		T x = (a = T(3.5));
		VERIFY(a.load() == T(3.5));
		VERIFY(x == T(3.5));
	}
	{
		Atomic a(T(4.5));
		T v = a;
		VERIFY(v == T(4.5));
	}
	{
		Atomic a(T(-1.5));
		VERIFY(a.exchange(T(4.5)) == T(-1.5));
		VERIFY(a.load() == T(4.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == a.compare_exchange_weak(expected, T(3.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.0));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.0;
		VERIFY(false == a.compare_exchange_weak(expected, T(2.5), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == a.compare_exchange_strong(expected, T(2.5), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 1.5;
		VERIFY(false == a.compare_exchange_strong(expected, T(2.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == a.compare_exchange_weak(expected, T(2.0)));
		VERIFY(a.load() == T(2.0));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.0;
		VERIFY(false == a.compare_exchange_weak(expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = nan;
		VERIFY(false == a.compare_exchange_weak(expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(nan);
		T expected = 3.0;
		VERIFY(false == a.compare_exchange_weak(expected, T(2.5)));
		VERIFY(hamon::isnan(a.load()));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(nan);
		T expected = nan;
		VERIFY(true == a.compare_exchange_weak(expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 1.5;
		VERIFY(false == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = nan;
		VERIFY(false == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(nan);
		T expected = 3.0;
		VERIFY(false == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(hamon::isnan(a.load()));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(nan);
		T expected = nan;
		VERIFY(true == a.compare_exchange_strong(expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_add(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_sub(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(0.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_max(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_max(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_min(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_min(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(2.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fmaximum(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fmaximum(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(+0.0));
		T before = a.fetch_fmaximum(T(-0.0));
		VERIFY( hamon::iszero (before));	// before == +0.0
		VERIFY(!hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		T before = a.fetch_fmaximum(T(+0.0));
		VERIFY( hamon::iszero (before));	// before == -0.0
		VERIFY( hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		T before = a.fetch_fmaximum(nan);
		VERIFY(before == T(1.0));		// before != nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fmaximum(T(1.0));
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fmaximum(nan);
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fminimum(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fminimum(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(2.5));
	}
	{
		Atomic a(T(+0.0));
		T before = a.fetch_fminimum(T(-0.0));
		VERIFY( hamon::iszero (before));	// before == +0.0
		VERIFY(!hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		T before = a.fetch_fminimum(T(+0.0));
		VERIFY( hamon::iszero (before));	// before == -0.0
		VERIFY( hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		T before = a.fetch_fminimum(nan);
		VERIFY(before == T(1.0));		// before != nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fminimum(T(1.0));
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fminimum(nan);
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fmaximum_num(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.5));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fmaximum_num(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(+0.0));
		T before = a.fetch_fmaximum_num(T(-0.0));
		VERIFY( hamon::iszero (before));	// before == +0.0
		VERIFY(!hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		T before = a.fetch_fmaximum_num(T(+0.0));
		VERIFY( hamon::iszero (before));	// before == -0.0
		VERIFY( hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		T before = a.fetch_fmaximum_num(nan);
		VERIFY(before == T(1.0));		// before != nan
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fmaximum_num(T(1.0));
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fmaximum_num(nan);
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fminimum_num(T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = a.fetch_fminimum_num(T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(2.5));
	}
	{
		Atomic a(T(+0.0));
		T before = a.fetch_fminimum_num(T(-0.0));
		VERIFY( hamon::iszero (before));	// before == +0.0
		VERIFY(!hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		T before = a.fetch_fminimum_num(T(+0.0));
		VERIFY( hamon::iszero (before));	// before == -0.0
		VERIFY( hamon::signbit(before));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		T before = a.fetch_fminimum_num(nan);
		VERIFY(before == T(1.0));		// before != nan
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fminimum_num(T(1.0));
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		T before = a.fetch_fminimum_num(nan);
		VERIFY(hamon::isnan(before));	// before == nan
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3.0));
		a.store_add(T(2.5));
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		a.store_sub(T(2.5));
		VERIFY(a.load() == T(0.5));
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
		a.store_fmaximum(T(4));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		a.store_fmaximum(T(2));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(+0.0));
		a.store_fmaximum(T(-0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		a.store_fmaximum(T(+0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		a.store_fmaximum(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		a.store_fmaximum(T(1.0));
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		a.store_fmaximum(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3));
		a.store_fminimum(T(4));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		a.store_fminimum(T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(+0.0));
		a.store_fminimum(T(-0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		a.store_fminimum(T(+0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		a.store_fminimum(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		a.store_fminimum(T(1.0));
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(nan);
		a.store_fminimum(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3));
		a.store_fmaximum_num(T(4));
		VERIFY(a.load() == T(4));
	}
	{
		Atomic a(T(3));
		a.store_fmaximum_num(T(2));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(+0.0));
		a.store_fmaximum_num(T(-0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		a.store_fmaximum_num(T(+0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == +0.0
		VERIFY(!hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		a.store_fmaximum_num(nan);
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		a.store_fmaximum_num(T(1.0));
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		a.store_fmaximum_num(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3));
		a.store_fminimum_num(T(4));
		VERIFY(a.load() == T(3));
	}
	{
		Atomic a(T(3));
		a.store_fminimum_num(T(2));
		VERIFY(a.load() == T(2));
	}
	{
		Atomic a(T(+0.0));
		a.store_fminimum_num(T(-0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(-0.0));
		a.store_fminimum_num(T(+0.0));
		VERIFY( hamon::iszero (a.load()));	// load() == -0.0
		VERIFY( hamon::signbit(a.load()));
	}
	{
		Atomic a(T(1.0));
		a.store_fminimum_num(nan);
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		a.store_fminimum_num(T(1.0));
		VERIFY(a.load() == T(1.0));		// load() != nan
	}
	{
		Atomic a(nan);
		a.store_fminimum_num(nan);
		VERIFY(hamon::isnan(a.load()));	// load() == nan
	}
	{
		Atomic a(T(3.5));
		auto t = a += T(2.5);
		VERIFY(a.load() == T(6.0));
		VERIFY(t == T(6.0));
	}
	{
		Atomic a(T(3.5));
		auto t = a -= T(2.5);
		VERIFY(a.load() == T(1.0));
		VERIFY(t == T(1.0));
	}

	return true;
}

template <bool Volatile, typename T>
HAMON_CXX14_CONSTEXPR bool nonmember_test()
{
	using Atomic = hamon::conditional_t<Volatile, hamon::atomic<T> volatile, hamon::atomic<T>>;

	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();

	{
		Atomic a;
		VERIFY(hamon::atomic_load(&a) == T(0));
	}
	{
		Atomic a(T(2.5));
		VERIFY(hamon::atomic_load_explicit(&a, hamon::memory_order::seq_cst) == T(2.5));
	}
	{
		Atomic a(T(1));
		hamon::atomic_store(&a, T(-2.5));
		VERIFY(a.load() == T(-2.5));
	}
	{
		Atomic a(T(1));
		hamon::atomic_store_explicit(&a, T(3.5), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(3.5));
	}
	{
		Atomic a(T(-1.5));
		VERIFY(hamon::atomic_exchange(&a, T(4.5)) == T(-1.5));
		VERIFY(a.load() == T(4.5));
	}
	{
		Atomic a(T(-1.5));
		VERIFY(hamon::atomic_exchange_explicit(&a, T(4.5), hamon::memory_order::seq_cst) == T(-1.5));
		VERIFY(a.load() == T(4.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, T(3.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.0));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.0;
		VERIFY(false == hamon::atomic_compare_exchange_weak_explicit(&a, &expected, T(2.5), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, T(2.5), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(2.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 1.5;
		VERIFY(false == hamon::atomic_compare_exchange_strong_explicit(&a, &expected, T(2.0), hamon::memory_order::seq_cst, hamon::memory_order::seq_cst));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == hamon::atomic_compare_exchange_weak(&a, &expected, T(2.0)));
		VERIFY(a.load() == T(2.0));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.0;
		VERIFY(false == hamon::atomic_compare_exchange_weak(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = nan;
		VERIFY(false == hamon::atomic_compare_exchange_weak(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(nan);
		T expected = 3.0;
		VERIFY(false == hamon::atomic_compare_exchange_weak(&a, &expected, T(2.5)));
		VERIFY(hamon::isnan(a.load()));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(nan);
		T expected = nan;
		VERIFY(true == hamon::atomic_compare_exchange_weak(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(T(3.5));
		T expected = 3.5;
		VERIFY(true == hamon::atomic_compare_exchange_strong(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = 1.5;
		VERIFY(false == hamon::atomic_compare_exchange_strong(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(T(3.5));
		T expected = nan;
		VERIFY(false == hamon::atomic_compare_exchange_strong(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(3.5));
		VERIFY(expected == T(3.5));
	}
	{
		Atomic a(nan);
		T expected = 3.0;
		VERIFY(false == hamon::atomic_compare_exchange_strong(&a, &expected, T(2.5)));
		VERIFY(hamon::isnan(a.load()));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(nan);
		T expected = nan;
		VERIFY(true == hamon::atomic_compare_exchange_strong(&a, &expected, T(2.5)));
		VERIFY(a.load() == T(2.5));
		VERIFY(hamon::isnan(expected));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_add(&a, T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_add_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_sub(&a, T(2.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(0.5));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_sub_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(0.5));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_max(&a, T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.5));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_max_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_min(&a, T(3.5));
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(3.0));
	}
	{
		Atomic a(T(3.0));
		T before = hamon::atomic_fetch_min_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(before == T(3.0));
		VERIFY(a.load() == T(2.5));
	}
	{
		Atomic a(T(3.0));
		hamon::atomic_store_add(&a, T(2.5));
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		hamon::atomic_store_add_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(5.5));
	}
	{
		Atomic a(T(3.0));
		hamon::atomic_store_sub(&a, T(2.5));
		VERIFY(a.load() == T(0.5));
	}
	{
		Atomic a(T(3.0));
		hamon::atomic_store_sub_explicit(&a, T(2.5), hamon::memory_order::seq_cst);
		VERIFY(a.load() == T(0.5));
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
	return true;
}

template <typename T>
bool wait_test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicFloatingPointTest)
{
	EXPECT_TRUE((lock_free_test<float>()));
	EXPECT_TRUE((lock_free_test<double>()));
	EXPECT_TRUE((lock_free_test<long double>()));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, double>()));
#if !(defined(HAMON_CLANG) && HAMON_CLANG < 230000)
	// GCC  : long double はパディングを持つ。__builtin_clear_paddingビルトイン関数でクリアできる。
	// Clang: long double はパディングを持つ。__builtin_clear_paddingが実装されたのはClang-23。
	// MSVC : long double は double と同じ型。
	//
	// -> Clang-23以前では、atomic<long double> はまともに使えない
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, long double>()));
#endif

	EXPECT_TRUE((test<true, float>()));
	EXPECT_TRUE((test<true, double>()));
//	EXPECT_TRUE((test<true, long double>()));	// is_always_lock_free が false の場合、volatile版はオーバーロードの候補にならない

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, float>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((nonmember_test<false, double>()));

	EXPECT_TRUE((nonmember_test<true, float>()));
	EXPECT_TRUE((nonmember_test<true, double>()));

	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<float>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<long double>()));

	//EXPECT_TRUE((wait_test<float>()));
	//EXPECT_TRUE((wait_test<double>()));
	//EXPECT_TRUE((wait_test<long double>()));

	{
		hamon::atomic<float> x{0};
		std::thread t1
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x += 0.5;
				}
			}
		};
		std::thread t2
		{
			[&x]()
			{
				for (int i = 0; i < 1000; ++i)
				{
					x -= 1.5;
				}
			}
		};
		t1.join();
		t2.join();
		EXPECT_EQ(-1000, x);
	}
}

}	// namespace atomic_floating_point_test
}	// namespace hamon_atomic_test
