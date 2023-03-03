/**
 *	@file	unit_test_type_traits_copy_cv.cpp
 *
 *	@brief	copy_cv のテスト
 */

#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

#define HAMON_COPY_CV_TEST(T1, T2, T3)	\
	static_assert(hamon::is_same<hamon::copy_cv<T1, T2>::type, T3>::value, "");	\
	static_assert(hamon::is_same<hamon::copy_cv_t<T1, T2>,     T3>::value, "")

// 基本的なテスト
HAMON_COPY_CV_TEST(               int,                void,                int);
HAMON_COPY_CV_TEST(const          int,                void, const          int);
HAMON_COPY_CV_TEST(      volatile int,                void,       volatile int);
HAMON_COPY_CV_TEST(const volatile int,                void, const volatile int);

HAMON_COPY_CV_TEST(               int, const          void, const          int);
HAMON_COPY_CV_TEST(const          int, const          void, const          int);
HAMON_COPY_CV_TEST(      volatile int, const          void, const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const          void, const volatile int);

HAMON_COPY_CV_TEST(               int,       volatile void,       volatile int);
HAMON_COPY_CV_TEST(const          int,       volatile void, const volatile int);
HAMON_COPY_CV_TEST(      volatile int,       volatile void,       volatile int);
HAMON_COPY_CV_TEST(const volatile int,       volatile void, const volatile int);

HAMON_COPY_CV_TEST(               int, const volatile void, const volatile int);
HAMON_COPY_CV_TEST(const          int, const volatile void, const volatile int);
HAMON_COPY_CV_TEST(      volatile int, const volatile void, const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const volatile void, const volatile int);

HAMON_COPY_CV_TEST(               int,                float[2],                int);
HAMON_COPY_CV_TEST(const          int,                float[2], const          int);
HAMON_COPY_CV_TEST(      volatile int,                float[2],       volatile int);
HAMON_COPY_CV_TEST(const volatile int,                float[2], const volatile int);

HAMON_COPY_CV_TEST(               int, const          float[2], const          int);
HAMON_COPY_CV_TEST(const          int, const          float[2], const          int);
HAMON_COPY_CV_TEST(      volatile int, const          float[2], const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const          float[2], const volatile int);

HAMON_COPY_CV_TEST(               int,       volatile float[2],       volatile int);
HAMON_COPY_CV_TEST(const          int,       volatile float[2], const volatile int);
HAMON_COPY_CV_TEST(      volatile int,       volatile float[2],       volatile int);
HAMON_COPY_CV_TEST(const volatile int,       volatile float[2], const volatile int);

HAMON_COPY_CV_TEST(               int, const volatile float[2], const volatile int);
HAMON_COPY_CV_TEST(const          int, const volatile float[2], const volatile int);
HAMON_COPY_CV_TEST(      volatile int, const volatile float[2], const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const volatile float[2], const volatile int);

HAMON_COPY_CV_TEST(               int,                float[],                int);
HAMON_COPY_CV_TEST(const          int,                float[], const          int);
HAMON_COPY_CV_TEST(      volatile int,                float[],       volatile int);
HAMON_COPY_CV_TEST(const volatile int,                float[], const volatile int);

HAMON_COPY_CV_TEST(               int, const          float[], const          int);
HAMON_COPY_CV_TEST(const          int, const          float[], const          int);
HAMON_COPY_CV_TEST(      volatile int, const          float[], const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const          float[], const volatile int);

HAMON_COPY_CV_TEST(               int,       volatile float[],       volatile int);
HAMON_COPY_CV_TEST(const          int,       volatile float[], const volatile int);
HAMON_COPY_CV_TEST(      volatile int,       volatile float[],       volatile int);
HAMON_COPY_CV_TEST(const volatile int,       volatile float[], const volatile int);

HAMON_COPY_CV_TEST(               int, const volatile float[], const volatile int);
HAMON_COPY_CV_TEST(const          int, const volatile float[], const volatile int);
HAMON_COPY_CV_TEST(      volatile int, const volatile float[], const volatile int);
HAMON_COPY_CV_TEST(const volatile int, const volatile float[], const volatile int);

HAMON_COPY_CV_TEST(               int[2],                void,                int[2]);
HAMON_COPY_CV_TEST(const          int[2],                void, const          int[2]);
HAMON_COPY_CV_TEST(      volatile int[2],                void,       volatile int[2]);
HAMON_COPY_CV_TEST(const volatile int[2],                void, const volatile int[2]);

HAMON_COPY_CV_TEST(               int[2], const          void, const          int[2]);
HAMON_COPY_CV_TEST(const          int[2], const          void, const          int[2]);
HAMON_COPY_CV_TEST(      volatile int[2], const          void, const volatile int[2]);
HAMON_COPY_CV_TEST(const volatile int[2], const          void, const volatile int[2]);

HAMON_COPY_CV_TEST(               int[2],       volatile void,       volatile int[2]);
HAMON_COPY_CV_TEST(const          int[2],       volatile void, const volatile int[2]);
HAMON_COPY_CV_TEST(      volatile int[2],       volatile void,       volatile int[2]);
HAMON_COPY_CV_TEST(const volatile int[2],       volatile void, const volatile int[2]);

HAMON_COPY_CV_TEST(               int[2], const volatile void, const volatile int[2]);
HAMON_COPY_CV_TEST(const          int[2], const volatile void, const volatile int[2]);
HAMON_COPY_CV_TEST(      volatile int[2], const volatile void, const volatile int[2]);
HAMON_COPY_CV_TEST(const volatile int[2], const volatile void, const volatile int[2]);

HAMON_COPY_CV_TEST(               int[],                float,                int[]);
HAMON_COPY_CV_TEST(const          int[],                float, const          int[]);
HAMON_COPY_CV_TEST(      volatile int[],                float,       volatile int[]);
HAMON_COPY_CV_TEST(const volatile int[],                float, const volatile int[]);

HAMON_COPY_CV_TEST(               int[], const          float, const          int[]);
HAMON_COPY_CV_TEST(const          int[], const          float, const          int[]);
HAMON_COPY_CV_TEST(      volatile int[], const          float, const volatile int[]);
HAMON_COPY_CV_TEST(const volatile int[], const          float, const volatile int[]);

HAMON_COPY_CV_TEST(               int[],       volatile float,       volatile int[]);
HAMON_COPY_CV_TEST(const          int[],       volatile float, const volatile int[]);
HAMON_COPY_CV_TEST(      volatile int[],       volatile float,       volatile int[]);
HAMON_COPY_CV_TEST(const volatile int[],       volatile float, const volatile int[]);

HAMON_COPY_CV_TEST(               int[], const volatile float, const volatile int[]);
HAMON_COPY_CV_TEST(const          int[], const volatile float, const volatile int[]);
HAMON_COPY_CV_TEST(      volatile int[], const volatile float, const volatile int[]);
HAMON_COPY_CV_TEST(const volatile int[], const volatile float, const volatile int[]);

HAMON_COPY_CV_TEST(int,                int*,       int);
HAMON_COPY_CV_TEST(int, const          int*,       int);
HAMON_COPY_CV_TEST(int,       volatile int*,       int);
HAMON_COPY_CV_TEST(int, const volatile int*,       int);
HAMON_COPY_CV_TEST(int,                int&,       int);
HAMON_COPY_CV_TEST(int, const          int&,       int);
HAMON_COPY_CV_TEST(int,       volatile int&,       int);
HAMON_COPY_CV_TEST(int, const volatile int&,       int);
HAMON_COPY_CV_TEST(int,                int&&,      int);
HAMON_COPY_CV_TEST(int, const          int&&,      int);
HAMON_COPY_CV_TEST(int,       volatile int&&,      int);
HAMON_COPY_CV_TEST(int, const volatile int&&,      int);
HAMON_COPY_CV_TEST(int,                int(&)[2],  int);
HAMON_COPY_CV_TEST(int, const          int(&)[2],  int);
HAMON_COPY_CV_TEST(int,       volatile int(&)[2],  int);
HAMON_COPY_CV_TEST(int, const volatile int(&)[2],  int);
HAMON_COPY_CV_TEST(int,                int(&)[],   int);
HAMON_COPY_CV_TEST(int, const          int(&)[],   int);
HAMON_COPY_CV_TEST(int,       volatile int(&)[],   int);
HAMON_COPY_CV_TEST(int, const volatile int(&)[],   int);
HAMON_COPY_CV_TEST(int,                int(&&)[2], int);
HAMON_COPY_CV_TEST(int, const          int(&&)[2], int);
HAMON_COPY_CV_TEST(int,       volatile int(&&)[2], int);
HAMON_COPY_CV_TEST(int, const volatile int(&&)[2], int);
HAMON_COPY_CV_TEST(int,                int(&&)[],  int);
HAMON_COPY_CV_TEST(int, const          int(&&)[],  int);
HAMON_COPY_CV_TEST(int,       volatile int(&&)[],  int);
HAMON_COPY_CV_TEST(int, const volatile int(&&)[],  int);
HAMON_COPY_CV_TEST(int,                int(*)[2],  int);
HAMON_COPY_CV_TEST(int, const          int(*)[2],  int);
HAMON_COPY_CV_TEST(int,       volatile int(*)[2],  int);
HAMON_COPY_CV_TEST(int, const volatile int(*)[2],  int);
HAMON_COPY_CV_TEST(int,                int(*)[],   int);
HAMON_COPY_CV_TEST(int, const          int(*)[],   int);
HAMON_COPY_CV_TEST(int,       volatile int(*)[],   int);
HAMON_COPY_CV_TEST(int, const volatile int(*)[],   int);

// 参照の時は変化しない
HAMON_COPY_CV_TEST(               int&,                void, int               &);
HAMON_COPY_CV_TEST(const          int&,                void, int const         &);
HAMON_COPY_CV_TEST(      volatile int&,                void, int       volatile&);
HAMON_COPY_CV_TEST(const volatile int&,                void, int const volatile&);

HAMON_COPY_CV_TEST(               int&, const          void, int               &);
HAMON_COPY_CV_TEST(const          int&, const          void, int const         &);
HAMON_COPY_CV_TEST(      volatile int&, const          void, int       volatile&);
HAMON_COPY_CV_TEST(const volatile int&, const          void, int const volatile&);

HAMON_COPY_CV_TEST(               int&,       volatile void, int               &);
HAMON_COPY_CV_TEST(const          int&,       volatile void, int const         &);
HAMON_COPY_CV_TEST(      volatile int&,       volatile void, int       volatile&);
HAMON_COPY_CV_TEST(const volatile int&,       volatile void, int const volatile&);

HAMON_COPY_CV_TEST(               int&, const volatile void, int               &);
HAMON_COPY_CV_TEST(const          int&, const volatile void, int const         &);
HAMON_COPY_CV_TEST(      volatile int&, const volatile void, int       volatile&);
HAMON_COPY_CV_TEST(const volatile int&, const volatile void, int const volatile&);

HAMON_COPY_CV_TEST(               int(&)[2],                void, int               (&)[2]);
HAMON_COPY_CV_TEST(const          int(&)[2],                void, int const         (&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&)[2],                void, int       volatile(&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&)[2],                void, int const volatile(&)[2]);

HAMON_COPY_CV_TEST(               int(&)[2], const          void, int               (&)[2]);
HAMON_COPY_CV_TEST(const          int(&)[2], const          void, int const         (&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&)[2], const          void, int       volatile(&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&)[2], const          void, int const volatile(&)[2]);

HAMON_COPY_CV_TEST(               int(&)[2],       volatile void, int               (&)[2]);
HAMON_COPY_CV_TEST(const          int(&)[2],       volatile void, int const         (&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&)[2],       volatile void, int       volatile(&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&)[2],       volatile void, int const volatile(&)[2]);

HAMON_COPY_CV_TEST(               int(&)[2], const volatile void, int               (&)[2]);
HAMON_COPY_CV_TEST(const          int(&)[2], const volatile void, int const         (&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&)[2], const volatile void, int       volatile(&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&)[2], const volatile void, int const volatile(&)[2]);

HAMON_COPY_CV_TEST(               int(&)[],                void, int               (&)[]);
HAMON_COPY_CV_TEST(const          int(&)[],                void, int const         (&)[]);
HAMON_COPY_CV_TEST(      volatile int(&)[],                void, int       volatile(&)[]);
HAMON_COPY_CV_TEST(const volatile int(&)[],                void, int const volatile(&)[]);

HAMON_COPY_CV_TEST(               int(&)[], const          void, int               (&)[]);
HAMON_COPY_CV_TEST(const          int(&)[], const          void, int const         (&)[]);
HAMON_COPY_CV_TEST(      volatile int(&)[], const          void, int       volatile(&)[]);
HAMON_COPY_CV_TEST(const volatile int(&)[], const          void, int const volatile(&)[]);

HAMON_COPY_CV_TEST(               int(&)[],       volatile void, int               (&)[]);
HAMON_COPY_CV_TEST(const          int(&)[],       volatile void, int const         (&)[]);
HAMON_COPY_CV_TEST(      volatile int(&)[],       volatile void, int       volatile(&)[]);
HAMON_COPY_CV_TEST(const volatile int(&)[],       volatile void, int const volatile(&)[]);

HAMON_COPY_CV_TEST(               int(&)[], const volatile void, int               (&)[]);
HAMON_COPY_CV_TEST(const          int(&)[], const volatile void, int const         (&)[]);
HAMON_COPY_CV_TEST(      volatile int(&)[], const volatile void, int       volatile(&)[]);
HAMON_COPY_CV_TEST(const volatile int(&)[], const volatile void, int const volatile(&)[]);

HAMON_COPY_CV_TEST(               int&&,                void, int               &&);
HAMON_COPY_CV_TEST(const          int&&,                void, int const         &&);
HAMON_COPY_CV_TEST(      volatile int&&,                void, int       volatile&&);
HAMON_COPY_CV_TEST(const volatile int&&,                void, int const volatile&&);

HAMON_COPY_CV_TEST(               int&&, const          void, int               &&);
HAMON_COPY_CV_TEST(const          int&&, const          void, int const         &&);
HAMON_COPY_CV_TEST(      volatile int&&, const          void, int       volatile&&);
HAMON_COPY_CV_TEST(const volatile int&&, const          void, int const volatile&&);

HAMON_COPY_CV_TEST(               int&&,       volatile void, int               &&);
HAMON_COPY_CV_TEST(const          int&&,       volatile void, int const         &&);
HAMON_COPY_CV_TEST(      volatile int&&,       volatile void, int       volatile&&);
HAMON_COPY_CV_TEST(const volatile int&&,       volatile void, int const volatile&&);

HAMON_COPY_CV_TEST(               int&&, const volatile void, int               &&);
HAMON_COPY_CV_TEST(const          int&&, const volatile void, int const         &&);
HAMON_COPY_CV_TEST(      volatile int&&, const volatile void, int       volatile&&);
HAMON_COPY_CV_TEST(const volatile int&&, const volatile void, int const volatile&&);

HAMON_COPY_CV_TEST(               int(&&)[2],                void, int               (&&)[2]);
HAMON_COPY_CV_TEST(const          int(&&)[2],                void, int const         (&&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&&)[2],                void, int       volatile(&&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&&)[2],                void, int const volatile(&&)[2]);

HAMON_COPY_CV_TEST(               int(&&)[2], const          void, int               (&&)[2]);
HAMON_COPY_CV_TEST(const          int(&&)[2], const          void, int const         (&&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&&)[2], const          void, int       volatile(&&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&&)[2], const          void, int const volatile(&&)[2]);

HAMON_COPY_CV_TEST(               int(&&)[2],       volatile void, int               (&&)[2]);
HAMON_COPY_CV_TEST(const          int(&&)[2],       volatile void, int const         (&&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&&)[2],       volatile void, int       volatile(&&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&&)[2],       volatile void, int const volatile(&&)[2]);

HAMON_COPY_CV_TEST(               int(&&)[2], const volatile void, int               (&&)[2]);
HAMON_COPY_CV_TEST(const          int(&&)[2], const volatile void, int const         (&&)[2]);
HAMON_COPY_CV_TEST(      volatile int(&&)[2], const volatile void, int       volatile(&&)[2]);
HAMON_COPY_CV_TEST(const volatile int(&&)[2], const volatile void, int const volatile(&&)[2]);

HAMON_COPY_CV_TEST(               int(&&)[],                void, int               (&&)[]);
HAMON_COPY_CV_TEST(const          int(&&)[],                void, int const         (&&)[]);
HAMON_COPY_CV_TEST(      volatile int(&&)[],                void, int       volatile(&&)[]);
HAMON_COPY_CV_TEST(const volatile int(&&)[],                void, int const volatile(&&)[]);

HAMON_COPY_CV_TEST(               int(&&)[], const          void, int               (&&)[]);
HAMON_COPY_CV_TEST(const          int(&&)[], const          void, int const         (&&)[]);
HAMON_COPY_CV_TEST(      volatile int(&&)[], const          void, int       volatile(&&)[]);
HAMON_COPY_CV_TEST(const volatile int(&&)[], const          void, int const volatile(&&)[]);

HAMON_COPY_CV_TEST(               int(&&)[],       volatile void, int               (&&)[]);
HAMON_COPY_CV_TEST(const          int(&&)[],       volatile void, int const         (&&)[]);
HAMON_COPY_CV_TEST(      volatile int(&&)[],       volatile void, int       volatile(&&)[]);
HAMON_COPY_CV_TEST(const volatile int(&&)[],       volatile void, int const volatile(&&)[]);

HAMON_COPY_CV_TEST(               int(&&)[], const volatile void, int               (&&)[]);
HAMON_COPY_CV_TEST(const          int(&&)[], const volatile void, int const         (&&)[]);
HAMON_COPY_CV_TEST(      volatile int(&&)[], const volatile void, int       volatile(&&)[]);
HAMON_COPY_CV_TEST(const volatile int(&&)[], const volatile void, int const volatile(&&)[]);

// ポインタの時 cv修飾が付く位置に注意
HAMON_COPY_CV_TEST(               int*,                void,                int*);
HAMON_COPY_CV_TEST(const          int*,                void, const          int*);
HAMON_COPY_CV_TEST(      volatile int*,                void,       volatile int*);
HAMON_COPY_CV_TEST(const volatile int*,                void, const volatile int*);

HAMON_COPY_CV_TEST(               int*, const          void,                int* const);
HAMON_COPY_CV_TEST(const          int*, const          void, const          int* const);
HAMON_COPY_CV_TEST(      volatile int*, const          void,       volatile int* const);
HAMON_COPY_CV_TEST(const volatile int*, const          void, const volatile int* const);

HAMON_COPY_CV_TEST(               int*,       volatile void,                int* volatile);
HAMON_COPY_CV_TEST(const          int*,       volatile void, const          int* volatile);
HAMON_COPY_CV_TEST(      volatile int*,       volatile void,       volatile int* volatile);
HAMON_COPY_CV_TEST(const volatile int*,       volatile void, const volatile int* volatile);

HAMON_COPY_CV_TEST(               int*, const volatile void,                int* const volatile);
HAMON_COPY_CV_TEST(const          int*, const volatile void, const          int* const volatile);
HAMON_COPY_CV_TEST(      volatile int*, const volatile void,       volatile int* const volatile);
HAMON_COPY_CV_TEST(const volatile int*, const volatile void, const volatile int* const volatile);

HAMON_COPY_CV_TEST(               int(*)[2],                void,                int(*)[2]);
HAMON_COPY_CV_TEST(const          int(*)[2],                void, const          int(*)[2]);
HAMON_COPY_CV_TEST(      volatile int(*)[2],                void,       volatile int(*)[2]);
HAMON_COPY_CV_TEST(const volatile int(*)[2],                void, const volatile int(*)[2]);

HAMON_COPY_CV_TEST(               int(*)[2], const          void,                int(* const)[2]);
HAMON_COPY_CV_TEST(const          int(*)[2], const          void, const          int(* const)[2]);
HAMON_COPY_CV_TEST(      volatile int(*)[2], const          void,       volatile int(* const)[2]);
HAMON_COPY_CV_TEST(const volatile int(*)[2], const          void, const volatile int(* const)[2]);

HAMON_COPY_CV_TEST(               int(*)[2],       volatile void,                int(* volatile)[2]);
HAMON_COPY_CV_TEST(const          int(*)[2],       volatile void, const          int(* volatile)[2]);
HAMON_COPY_CV_TEST(      volatile int(*)[2],       volatile void,       volatile int(* volatile)[2]);
HAMON_COPY_CV_TEST(const volatile int(*)[2],       volatile void, const volatile int(* volatile)[2]);

HAMON_COPY_CV_TEST(               int(*)[2], const volatile void,                int(* const volatile)[2]);
HAMON_COPY_CV_TEST(const          int(*)[2], const volatile void, const          int(* const volatile)[2]);
HAMON_COPY_CV_TEST(      volatile int(*)[2], const volatile void,       volatile int(* const volatile)[2]);
HAMON_COPY_CV_TEST(const volatile int(*)[2], const volatile void, const volatile int(* const volatile)[2]);

HAMON_COPY_CV_TEST(               int(*)[],                void,                int(*)[]);
HAMON_COPY_CV_TEST(const          int(*)[],                void, const          int(*)[]);
HAMON_COPY_CV_TEST(      volatile int(*)[],                void,       volatile int(*)[]);
HAMON_COPY_CV_TEST(const volatile int(*)[],                void, const volatile int(*)[]);

HAMON_COPY_CV_TEST(               int(*)[], const          void,                int(* const)[]);
HAMON_COPY_CV_TEST(const          int(*)[], const          void, const          int(* const)[]);
HAMON_COPY_CV_TEST(      volatile int(*)[], const          void,       volatile int(* const)[]);
HAMON_COPY_CV_TEST(const volatile int(*)[], const          void, const volatile int(* const)[]);

HAMON_COPY_CV_TEST(               int(*)[],       volatile void,                int(* volatile)[]);
HAMON_COPY_CV_TEST(const          int(*)[],       volatile void, const          int(* volatile)[]);
HAMON_COPY_CV_TEST(      volatile int(*)[],       volatile void,       volatile int(* volatile)[]);
HAMON_COPY_CV_TEST(const volatile int(*)[],       volatile void, const volatile int(* volatile)[]);

HAMON_COPY_CV_TEST(               int(*)[], const volatile void,                int(* const volatile)[]);
HAMON_COPY_CV_TEST(const          int(*)[], const volatile void, const          int(* const volatile)[]);
HAMON_COPY_CV_TEST(      volatile int(*)[], const volatile void,       volatile int(* const volatile)[]);
HAMON_COPY_CV_TEST(const volatile int(*)[], const volatile void, const volatile int(* const volatile)[]);

#undef HAMON_COPY_CV_TEST
