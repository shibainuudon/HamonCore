/**
 *	@file	unit_test_concepts_derived_from.cpp
 *
 *	@brief	derived_from のテスト
 */

#include <hamon/concepts/derived_from.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_DERIVED_FROM_TEST(B, T1, T2)	\
	static_assert(B == hamon::derived_from<T1, T2>, "");	\
	static_assert(B == hamon::derived_from_t<T1, T2>::value, "")
#else
#  define HAMON_DERIVED_FROM_TEST(B, T1, T2)	\
	static_assert(B == hamon::derived_from<T1, T2>::value, "");	\
	static_assert(B == hamon::derived_from_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace derived_from_test
{

HAMON_DERIVED_FROM_TEST(false, int, int);
HAMON_DERIVED_FROM_TEST(false, int&, int);
HAMON_DERIVED_FROM_TEST(false, int, int&);
HAMON_DERIVED_FROM_TEST(false, int&&, int&);
HAMON_DERIVED_FROM_TEST(false, const int, int);
HAMON_DERIVED_FROM_TEST(false, const int, const int);

struct A { };
HAMON_DERIVED_FROM_TEST(true,  A,                A);
HAMON_DERIVED_FROM_TEST(true,  A,                A const);
HAMON_DERIVED_FROM_TEST(true,  A,                A volatile);
HAMON_DERIVED_FROM_TEST(true,  A,                A const volatile);
HAMON_DERIVED_FROM_TEST(true,  A const,          A);
HAMON_DERIVED_FROM_TEST(true,  A const,          A const);
HAMON_DERIVED_FROM_TEST(true,  A const,          A volatile);
HAMON_DERIVED_FROM_TEST(true,  A const,          A const volatile);
HAMON_DERIVED_FROM_TEST(true,  A       volatile, A);
HAMON_DERIVED_FROM_TEST(true,  A       volatile, A const);
HAMON_DERIVED_FROM_TEST(true,  A       volatile, A volatile);
HAMON_DERIVED_FROM_TEST(true,  A       volatile, A const volatile);
HAMON_DERIVED_FROM_TEST(true,  A const volatile, A);
HAMON_DERIVED_FROM_TEST(true,  A const volatile, A const);
HAMON_DERIVED_FROM_TEST(true,  A const volatile, A volatile);
HAMON_DERIVED_FROM_TEST(true,  A const volatile, A const volatile);
HAMON_DERIVED_FROM_TEST(false, A&, A&);

struct B : A { };
HAMON_DERIVED_FROM_TEST(false, A, B);
HAMON_DERIVED_FROM_TEST(true,  B, A);
HAMON_DERIVED_FROM_TEST(true,  B const, A);
HAMON_DERIVED_FROM_TEST(true,  B, A const);
HAMON_DERIVED_FROM_TEST(true,  B volatile, A const);
HAMON_DERIVED_FROM_TEST(false, A&, B&);
HAMON_DERIVED_FROM_TEST(false, B&, A&);

struct C : private A { };
HAMON_DERIVED_FROM_TEST(false, A, C);
HAMON_DERIVED_FROM_TEST(false, C, A);

struct D : A { };
struct E : B, D { };
HAMON_DERIVED_FROM_TEST(false, A, E);
HAMON_DERIVED_FROM_TEST(false, E, A);

}	// namespace derived_from_test

}	// namespace hamon_concepts_test

#undef HAMON_DERIVED_FROM_TEST
