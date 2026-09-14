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
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false, long double>()));

	//EXPECT_TRUE((test<true, float>()));
	//EXPECT_TRUE((test<true, double>()));
	//EXPECT_TRUE((test<true, long double>()));

	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<float>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<double>()));
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((wait_constexpr_test<long double>()));

	//EXPECT_TRUE((wait_test<float>()));
	//EXPECT_TRUE((wait_test<double>()));
	//EXPECT_TRUE((wait_test<long double>()));
}

}	// namespace atomic_floating_point_test
}	// namespace hamon_atomic_test
