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

//#include <thread>

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

#undef VERIFY

GTEST_TEST(AtomicTest, AtomicFlagTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<false>()));
	EXPECT_TRUE((test<true>()));
}

}	// namespace atomic_flag_test
}	// namespace hamon_atomic_test
