/**
 *	@file	unit_test_type_traits_is_nothrow_convertible.cpp
 *
 *	@brief	is_nothrow_convertible のテスト
 */

#include <hamon/type_traits/is_nothrow_convertible.hpp>

namespace hamon_type_traits_test
{

namespace is_nothrow_convertible_test
{

struct A {};

struct B
{
	operator A() { return a; } A a;
};

struct C
{
	operator A() noexcept { return a; } A a;
};

struct D
{
	D(A const&) {}
};

struct E
{
	E(A const&) noexcept {}
};

struct F
{
	explicit F(A const&) noexcept {}
};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_IS_NOTHROW_CONVERTIBLE_TEST(b, From, To)	\
	static_assert(hamon::is_nothrow_convertible_v<From, To>      == b, #From ", " #To);	\
	static_assert(hamon::is_nothrow_convertible<From, To>::value == b, #From ", " #To);	\
	static_assert(hamon::is_nothrow_convertible<From, To>()      == b, #From ", " #To)

#else

#define HAMON_IS_NOTHROW_CONVERTIBLE_TEST(b, From, To)	\
	static_assert(hamon::is_nothrow_convertible<From, To>::value == b, #From ", " #To);	\
	static_assert(hamon::is_nothrow_convertible<From, To>()      == b, #From ", " #To)

#endif

HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, int);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, double);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int, char);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int, void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int*);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int[]);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int[], int[]);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int, int[3]);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int[3], int[3]);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const, int);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int* const, int*);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int const*, int*);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int*, int);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, int*, char*);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int*, void*);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int&, int);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const&, int);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int&, long);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  int const&, long);

HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,                void,                void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,                void, const          void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,                void,       volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,                void, const volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void,                void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void, const          void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void,       volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const          void, const volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void,                void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void, const          void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void,       volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,       volatile void, const volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void,                void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void, const          void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void,       volatile void);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true, const volatile void, const volatile void);

HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, A, B);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, B, A);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, A, C);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  C, A);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, A, D);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, D, A);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(true,  A, E);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, E, A);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, A, F);
HAMON_IS_NOTHROW_CONVERTIBLE_TEST(false, F, A);

#undef HAMON_IS_NOTHROW_CONVERTIBLE_TEST

}	// namespace is_nothrow_convertible_test

}	// namespace hamon_type_traits_test
