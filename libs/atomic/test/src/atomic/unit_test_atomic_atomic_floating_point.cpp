/**
 *	@file	unit_test_atomic_atomic_floating_point.cpp
 *
 *	@brief	atomic<floating-point-type> のテスト
 */

#include <hamon/atomic/atomic.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

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
		}
	}
	{
		hamon::atomic<T> volatile a;
		if (hamon::atomic<T>::is_always_lock_free)
		{
			VERIFY(a.is_lock_free());
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
	//{
	//	Atomic a(T(3));
	//	T before = a.fetch_add(T(2));
	//	VERIFY(before == T(3));
	//	VERIFY(a.load() == T(5));
	//}
	//{
	//	Atomic a(T(3));
	//	T before = a.fetch_sub(T(2));
	//	VERIFY(before == T(3));
	//	VERIFY(a.load() == T(1));
	//}
	//{
	//	Atomic a(T(2));
	//	T before = a.fetch_max(T(3));
	//	VERIFY(before == T(2));
	//	VERIFY(a.load() == T(3));
	//}
	//{
	//	Atomic a(T(2));
	//	T before = a.fetch_max(T(1));
	//	VERIFY(before == T(2));
	//	VERIFY(a.load() == T(2));
	//}
	//{
	//	Atomic a(T(2));
	//	T before = a.fetch_min(T(3));
	//	VERIFY(before == T(2));
	//	VERIFY(a.load() == T(2));
	//}
	//{
	//	Atomic a(T(2));
	//	T before = a.fetch_min(T(1));
	//	VERIFY(before == T(2));
	//	VERIFY(a.load() == T(1));

	// TODO: fetch_fmaximum

	// TODO: fetch_fminimum

	// TODO: fetch_fmaximum_num

	// TODO: fetch_fminimum_num

	//}
	//{
	//	Atomic a(T(3));
	//	a.store_add(T(2));
	//	VERIFY(a.load() == T(5));
	//}
	//{
	//	Atomic a(T(3));
	//	a.store_sub(T(2));
	//	VERIFY(a.load() == T(1));
	//}
	//{
	//	Atomic a(T(3));
	//	a.store_max(T(4));
	//	VERIFY(a.load() == T(4));
	//}
	//{
	//	Atomic a(T(3));
	//	a.store_max(T(2));
	//	VERIFY(a.load() == T(3));
	//}
	//{
	//	Atomic a(T(3));
	//	a.store_min(T(4));
	//	VERIFY(a.load() == T(3));
	//}
	//{
	//	Atomic a(T(3));
	//	a.store_min(T(2));
	//	VERIFY(a.load() == T(2));
	//}

	// TODO: store_fmaximum

	// TODO: store_fminimum

	// TODO: store_fmaximum_num

	// TODO: store_fminimum_num

	//{
	//	Atomic a(T(3));
	//	auto t = a += T(2);
	//	VERIFY(a.load() == T(5));
	//	VERIFY(t == T(5));
	//}
	//{
	//	Atomic a(T(3));
	//	auto t = a -= T(2);
	//	VERIFY(a.load() == T(1));
	//	VERIFY(t == T(1));
	//}

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
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, long double>()));
#endif

	EXPECT_TRUE((test<true, float>()));
	EXPECT_TRUE((test<true, double>()));
//	EXPECT_TRUE((test<true, long double>()));	// is_always_lock_free が false の場合、volatile版はオーバーロードの候補にならない

	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<float>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<long double>()));

	//EXPECT_TRUE((wait_test<float>()));
	//EXPECT_TRUE((wait_test<double>()));
	//EXPECT_TRUE((wait_test<long double>()));
}

}	// namespace atomic_floating_point_test
}	// namespace hamon_atomic_test
