/**
 *	@file	unit_test_type_traits_add_cv.cpp
 *
 *	@brief	add_cv のテスト
 */

#include <hamon/type_traits/add_cv.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

HAMON_TRANSFORM_TEST(hamon::add_cv, /**/,           const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, const,          const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile, const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv,                &,                &);
HAMON_TRANSFORM_TEST(hamon::add_cv, const          &, const          &);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile &,       volatile &);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile &, const volatile &);
HAMON_TRANSFORM_TEST(hamon::add_cv, *,               *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, *const,          *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, *      volatile, *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, *const volatile, *const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, const          *, const          * const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile *,       volatile * const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile *, const volatile * const volatile);
HAMON_TRANSFORM_TEST(hamon::add_cv,               [2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const         [2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile[2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile[2], const volatile[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv,                (&)[2],                (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const          (&)[2], const          (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile (&)[2],       volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile (&)[2], const volatile (&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv,                &&,                &&);
HAMON_TRANSFORM_TEST(hamon::add_cv, const          &&, const          &&);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile &&,       volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile &&, const volatile &&);
HAMON_TRANSFORM_TEST(hamon::add_cv,                (&&)[2],                (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const          (&&)[2], const          (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv,       volatile (&&)[2],       volatile (&&)[2]);
HAMON_TRANSFORM_TEST(hamon::add_cv, const volatile (&&)[2], const volatile (&&)[2]);

#define HAMON_ADD_CV_TEST(T1, T2)	\
	static_assert(hamon::is_same<hamon::add_cv_t<T1>, T2>::value, "");	\
	static_assert(hamon::is_same<hamon::add_cv<T1>::type, T2>::value, "")

HAMON_ADD_CV_TEST(               void, const volatile void);
HAMON_ADD_CV_TEST(const          void, const volatile void);
HAMON_ADD_CV_TEST(      volatile void, const volatile void);
HAMON_ADD_CV_TEST(const volatile void, const volatile void);
HAMON_ADD_CV_TEST(               void*,                void* const volatile);
HAMON_ADD_CV_TEST(const          void*, const          void* const volatile);
HAMON_ADD_CV_TEST(      volatile void*,       volatile void* const volatile);
HAMON_ADD_CV_TEST(const volatile void*, const volatile void* const volatile);
HAMON_ADD_CV_TEST(int(int), int(int));
HAMON_ADD_CV_TEST(void (UDT::*)(void), void (UDT::* const volatile)(void));
HAMON_ADD_CV_TEST(int (UDT::*)(int), int (UDT::* const volatile)(int));
HAMON_ADD_CV_TEST(int (UDT::*)(int, float), int (UDT::* const volatile)(int, float));
HAMON_ADD_CV_TEST(int (UDT::*)(int) const, int (UDT::* const volatile)(int) const);
HAMON_ADD_CV_TEST(int (UDT::*)(int) volatile, int (UDT::* const volatile)(int) volatile);
HAMON_ADD_CV_TEST(int (UDT::*)(int) const volatile, int (UDT::* const volatile)(int) const volatile);
HAMON_ADD_CV_TEST(int (UDT::*), int (UDT::* const volatile));
HAMON_ADD_CV_TEST(const float (UDT::*), const float (UDT::* const volatile));

#undef HAMON_ADD_CV_TEST
