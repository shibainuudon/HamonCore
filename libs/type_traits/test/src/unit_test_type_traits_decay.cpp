/**
 *	@file	unit_test_type_traits_decay.cpp
 *
 *	@brief	decay のテスト
 */

#include <hamon/type_traits/decay.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include "type_traits_test_utility.hpp"

#define HAMON_DECAY_TEST_IMPL(T1, T2)	\
	static_assert(std::is_same<hamon::decay<T1>::type, T2>::value, #T1 ", " #T2);	\
	static_assert(std::is_same<hamon::decay_t<T1>,     T2>::value, #T1 ", " #T2)

#define HAMON_DECAY_TEST(T)	\
	HAMON_DECAY_TEST_IMPL(               T, T);	\
	HAMON_DECAY_TEST_IMPL(const          T, T);	\
	HAMON_DECAY_TEST_IMPL(      volatile T, T);	\
	HAMON_DECAY_TEST_IMPL(const volatile T, T);	\
	HAMON_DECAY_TEST_IMPL(               T&, T);	\
	HAMON_DECAY_TEST_IMPL(const          T&, T);	\
	HAMON_DECAY_TEST_IMPL(      volatile T&, T);	\
	HAMON_DECAY_TEST_IMPL(const volatile T&, T);	\
	HAMON_DECAY_TEST_IMPL(               T&&, T);	\
	HAMON_DECAY_TEST_IMPL(const          T&&, T);	\
	HAMON_DECAY_TEST_IMPL(      volatile T&&, T);	\
	HAMON_DECAY_TEST_IMPL(const volatile T&&, T);	\
	HAMON_DECAY_TEST_IMPL(               T*,                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T*, const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T*,       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T*, const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T*&,                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T*&, const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T*&,       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T*&, const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T*&&,                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T*&&, const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T*&&,       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T*&&, const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T[2],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T[3], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T[4],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T[5], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T[],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T[], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T[],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T[], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T(*)[2],                T(*)[2]);	\
	HAMON_DECAY_TEST_IMPL(const          T(*)[3], const          T(*)[3]);	\
	HAMON_DECAY_TEST_IMPL(      volatile T(*)[4],       volatile T(*)[4]);	\
	HAMON_DECAY_TEST_IMPL(const volatile T(*)[5], const volatile T(*)[5]);	\
	HAMON_DECAY_TEST_IMPL(               T(&)[2],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T(&)[3], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T(&)[4],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T(&)[5], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T(&)[],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T(&)[], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T(&)[],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T(&)[], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T(&&)[2],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T(&&)[3], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T(&&)[4],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T(&&)[5], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(               T(&&)[],                T*);	\
	HAMON_DECAY_TEST_IMPL(const          T(&&)[], const          T*);	\
	HAMON_DECAY_TEST_IMPL(      volatile T(&&)[],       volatile T*);	\
	HAMON_DECAY_TEST_IMPL(const volatile T(&&)[], const volatile T*);	\
	HAMON_DECAY_TEST_IMPL(T(T), T(*)(T));	\
	HAMON_DECAY_TEST_IMPL(T(void), T(*)(void));	\
	HAMON_DECAY_TEST_IMPL(void(T), void(*)(T));	\
	HAMON_DECAY_TEST_IMPL(T(T, T), T(*)(T, T))

HAMON_DECAY_TEST(int);
HAMON_DECAY_TEST(UDT);
HAMON_DECAY_TEST_IMPL(f1, f1);
HAMON_DECAY_TEST_IMPL(f2, f2);
HAMON_DECAY_TEST_IMPL(f3, f3);
HAMON_DECAY_TEST_IMPL(mf1, mf1);
HAMON_DECAY_TEST_IMPL(mf2, mf2);
HAMON_DECAY_TEST_IMPL(mf3, mf3);
HAMON_DECAY_TEST_IMPL(mf4, mf4);
HAMON_DECAY_TEST_IMPL(mp, mp);
HAMON_DECAY_TEST_IMPL(cmf, cmf);
HAMON_DECAY_TEST_IMPL(foo0_t, void (*)(void));
HAMON_DECAY_TEST_IMPL(foo1_t, void (*)(int));
HAMON_DECAY_TEST_IMPL(foo2_t, void (*)(int&, double));
HAMON_DECAY_TEST_IMPL(foo3_t, void (*)(int&, bool, int, int));
HAMON_DECAY_TEST_IMPL(foo4_t, void (*)(int, bool, int*, int[], int, int, int, int, int));

#undef HAMON_DECAY_TEST
#undef HAMON_DECAY_TEST_IMPL
