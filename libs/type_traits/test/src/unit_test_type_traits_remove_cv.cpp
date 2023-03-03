/**
 *	@file	unit_test_type_traits_remove_cv.cpp
 *
 *	@brief	remove_cv のテスト
 */

#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::remove_cv, /**/          , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const         , /**/);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile, /**/);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile, /**/);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                &,                &);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::remove_cv, *               , *               );
HAMON_TRANSFORM_TEST(hamon::remove_cv, * const         , *               );
HAMON_TRANSFORM_TEST(hamon::remove_cv, *       volatile, *               );
HAMON_TRANSFORM_TEST(hamon::remove_cv, * const volatile, *               );
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          *, const          *);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile *,       volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile *, const volatile *);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile [2],                [2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile [],                []);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (&)[],                (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (&)[], const          (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (&)[],       volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (&)[], const volatile (&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (&&)[2], const volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (&&)[],                (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (&&)[], const          (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (&&)[],       volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (&&)[], const volatile (&&)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (*)[2],                (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (*)[2], const          (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (*)[2],       volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (*)[2], const volatile (*)[2]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,                (*)[],                (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const          (*)[], const          (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv,       volatile (*)[],       volatile (*)[]);
HAMON_TRANSFORM_TEST(hamon::remove_cv, const volatile (*)[], const volatile (*)[]);

#define HAMON_REMOVE_CV_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::remove_cv_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::remove_cv<T1>::type, T2>::value, "")

HAMON_REMOVE_CV_TEST(               void, void);
HAMON_REMOVE_CV_TEST(const          void, void);
HAMON_REMOVE_CV_TEST(      volatile void, void);
HAMON_REMOVE_CV_TEST(const volatile void, void);
HAMON_REMOVE_CV_TEST(void(void), void(void));
HAMON_REMOVE_CV_TEST(int(void), int(void));
HAMON_REMOVE_CV_TEST(void(int), void(int));
HAMON_REMOVE_CV_TEST(int(int), int(int));
HAMON_REMOVE_CV_TEST(int(char, short), int(char, short));
HAMON_REMOVE_CV_TEST(int(float, double, long double), int(float, double, long double));
HAMON_REMOVE_CV_TEST(int(*)(int), int(*)(int));
HAMON_REMOVE_CV_TEST(int(&)(int), int(&)(int));
HAMON_REMOVE_CV_TEST(int(&&)(int), int(&&)(int));
HAMON_REMOVE_CV_TEST(void (UDT::*)(void), void (UDT::*)(void));
HAMON_REMOVE_CV_TEST(int (UDT::*)(int), int (UDT::*)(int));
HAMON_REMOVE_CV_TEST(int (UDT::*)(int, float), int (UDT::*)(int, float));
HAMON_REMOVE_CV_TEST(int (UDT::*)(int) const, int (UDT::*)(int) const);
HAMON_REMOVE_CV_TEST(int (UDT::*)(int) volatile, int (UDT::*)(int) volatile);
HAMON_REMOVE_CV_TEST(int (UDT::*)(int) const volatile, int (UDT::*)(int) const volatile);
HAMON_REMOVE_CV_TEST(int (UDT::*), int (UDT::*));
HAMON_REMOVE_CV_TEST(const float (UDT::*), const float (UDT::*));

#undef HAMON_REMOVE_CV_TEST
