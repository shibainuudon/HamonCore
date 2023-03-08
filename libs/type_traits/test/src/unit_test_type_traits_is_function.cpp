/**
 *	@file	unit_test_type_traits_is_function.cpp
 *
 *	@brief	is_function のテスト
 */

#include <hamon/type_traits/is_function.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "type_traits_test_utility.hpp"

namespace hamon_type_traits_test
{

namespace is_function_test
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_FUNCTION_TEST(b, T)	\
	static_assert(hamon::is_function_v<T>      == b, #T);	\
	static_assert(hamon::is_function<T>::value == b, #T);	\
	static_assert(hamon::is_function<T>{}()    == b, #T);	\
	static_assert(hamon::is_function<T>{}      == b, #T)

#else

#define HAMON_IS_FUNCTION_TEST(b, T)	\
	static_assert(hamon::is_function<T>::value == b, #T);	\
	static_assert(hamon::is_function<T>{}()    == b, #T);	\
	static_assert(hamon::is_function<T>{}      == b, #T)

#endif

typedef void  func1()                                       ;
typedef int   func2()                        const          ;
typedef int   func3(int)                           volatile ;
typedef void  func4(int, float)              const volatile ;
typedef int   func5(int, float, UDT)                        &;
typedef int   func6(int, float, int[], int&) const          &;
typedef float func7(UDT)                           volatile &;
typedef UDT   func8()                        const volatile &;
typedef int   func9(int, int, int, int, int)                &&;
typedef int   func10(int*)                   const          &&;
typedef int   func11(float)                        volatile &&;
typedef int   func12(double)                 const volatile &&;
typedef int   func13(...)                                   ;
typedef void  func14(int, ...)               const          ;
typedef float func15(float, ...)                   volatile ;
typedef int   func16(int, char, ...)         const volatile ;
typedef char  func17(int, int, int, ...)                    &;
typedef void  func18(float, ...)             const          &;
typedef int*  func19(int, ...)                     volatile &;
typedef int&  func20(...)                    const volatile &;
typedef int&& func21(int, ...)                              &&;
typedef int   func22(...)                    const          &&;
typedef int   func23(float, ...)                   volatile &&;
typedef int   func24(...)                    const volatile &&;

HAMON_IS_FUNCTION_TEST(true,  func1);
HAMON_IS_FUNCTION_TEST(false, func1*);
HAMON_IS_FUNCTION_TEST(false, func1&);
HAMON_IS_FUNCTION_TEST(false, func1&&);
HAMON_IS_FUNCTION_TEST(true, func2);
HAMON_IS_FUNCTION_TEST(true, func3);
HAMON_IS_FUNCTION_TEST(true, func4);
HAMON_IS_FUNCTION_TEST(true, func5);
HAMON_IS_FUNCTION_TEST(true, func6);
HAMON_IS_FUNCTION_TEST(true, func7);
HAMON_IS_FUNCTION_TEST(true, func8);
HAMON_IS_FUNCTION_TEST(true, func9);
HAMON_IS_FUNCTION_TEST(true, func10);
HAMON_IS_FUNCTION_TEST(true, func11);
HAMON_IS_FUNCTION_TEST(true, func12);
HAMON_IS_FUNCTION_TEST(true, func13);
HAMON_IS_FUNCTION_TEST(true, func14);
HAMON_IS_FUNCTION_TEST(true, func15);
HAMON_IS_FUNCTION_TEST(true, func16);
HAMON_IS_FUNCTION_TEST(true, func17);
HAMON_IS_FUNCTION_TEST(true, func18);
HAMON_IS_FUNCTION_TEST(true, func19);
HAMON_IS_FUNCTION_TEST(true, func20);
HAMON_IS_FUNCTION_TEST(true, func21);
HAMON_IS_FUNCTION_TEST(true, func22);
HAMON_IS_FUNCTION_TEST(true, func23);
HAMON_IS_FUNCTION_TEST(true, func24);

HAMON_IS_FUNCTION_TEST(true, int(int));
HAMON_IS_FUNCTION_TEST(true, int(int, int));
HAMON_IS_FUNCTION_TEST(true, int(int, int, int));
HAMON_IS_FUNCTION_TEST(true, int(int, int, int, int));
HAMON_IS_FUNCTION_TEST(true, int(int, ...));
HAMON_IS_FUNCTION_TEST(true, int(int, int, ...));
HAMON_IS_FUNCTION_TEST(true, int(int, int, int, ...));
HAMON_IS_FUNCTION_TEST(true, int(int, int, int, int, ...));

HAMON_IS_FUNCTION_TEST(false,                int);
HAMON_IS_FUNCTION_TEST(false, const          int);
HAMON_IS_FUNCTION_TEST(false,       volatile int);
HAMON_IS_FUNCTION_TEST(false, const volatile int);
HAMON_IS_FUNCTION_TEST(false, int*);
HAMON_IS_FUNCTION_TEST(false, int&);
HAMON_IS_FUNCTION_TEST(false, int&&);
HAMON_IS_FUNCTION_TEST(false, int[2]);
HAMON_IS_FUNCTION_TEST(false, int[]);
HAMON_IS_FUNCTION_TEST(false, int(*)[2]);
HAMON_IS_FUNCTION_TEST(false, int(*)[]);
HAMON_IS_FUNCTION_TEST(false, int(&)[2]);
HAMON_IS_FUNCTION_TEST(false, int(&)[]);
HAMON_IS_FUNCTION_TEST(false, int(&&)[2]);
HAMON_IS_FUNCTION_TEST(false, int(&&)[]);
HAMON_IS_FUNCTION_TEST(false, int(*)());
HAMON_IS_FUNCTION_TEST(false, int(*)(int));
HAMON_IS_FUNCTION_TEST(false, int(&)());
HAMON_IS_FUNCTION_TEST(false, int(&)(int));
HAMON_IS_FUNCTION_TEST(false, int(&&)());
HAMON_IS_FUNCTION_TEST(false, int(&&)(int));
HAMON_IS_FUNCTION_TEST(false, int(*)(...));
HAMON_IS_FUNCTION_TEST(false, int(&)(...));
HAMON_IS_FUNCTION_TEST(false, int(&&)(...));

HAMON_IS_FUNCTION_TEST(false,                void);
HAMON_IS_FUNCTION_TEST(false, const          void);
HAMON_IS_FUNCTION_TEST(false,       volatile void);
HAMON_IS_FUNCTION_TEST(false, const volatile void);

HAMON_IS_FUNCTION_TEST(false, bool);
HAMON_IS_FUNCTION_TEST(false, char);
HAMON_IS_FUNCTION_TEST(false, float);
HAMON_IS_FUNCTION_TEST(false, void*);
HAMON_IS_FUNCTION_TEST(false, hamon::nullptr_t);
HAMON_IS_FUNCTION_TEST(false, decltype(nullptr));
HAMON_IS_FUNCTION_TEST(false, enum_UDT);
HAMON_IS_FUNCTION_TEST(false, enum_class_UDT);
HAMON_IS_FUNCTION_TEST(false, UDT);
HAMON_IS_FUNCTION_TEST(false, POD_UDT);
HAMON_IS_FUNCTION_TEST(false, f1);
HAMON_IS_FUNCTION_TEST(false, f2);
HAMON_IS_FUNCTION_TEST(false, f3);
HAMON_IS_FUNCTION_TEST(false, mf1);
HAMON_IS_FUNCTION_TEST(false, mf2);
HAMON_IS_FUNCTION_TEST(false, mf3);
HAMON_IS_FUNCTION_TEST(false, mf4);
HAMON_IS_FUNCTION_TEST(false, mp);
HAMON_IS_FUNCTION_TEST(false, cmf);
HAMON_IS_FUNCTION_TEST(true,  foo0_t);
HAMON_IS_FUNCTION_TEST(false, foo0_t*);
HAMON_IS_FUNCTION_TEST(false, foo0_t&);
HAMON_IS_FUNCTION_TEST(false, foo0_t&&);
HAMON_IS_FUNCTION_TEST(true,  foo1_t);
HAMON_IS_FUNCTION_TEST(true,  foo2_t);
HAMON_IS_FUNCTION_TEST(true,  foo3_t);
HAMON_IS_FUNCTION_TEST(true,  foo4_t);

#undef HAMON_IS_FUNCTION_TEST

}	// namespace is_function_test

}	// namespace hamon_type_traits_test
