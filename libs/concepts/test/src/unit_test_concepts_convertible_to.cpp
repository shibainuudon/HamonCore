/**
 *	@file	unit_test_concepts_convertible_to.cpp
 *
 *	@brief	convertible_to のテスト
 */

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CONVERTIBLE_TO_TEST(B, T1, T2)	\
	static_assert(B == hamon::convertible_to<T1, T2>, "");	\
	static_assert(B == hamon::convertible_to_t<T1, T2>::value, "")
#else
#  define HAMON_CONVERTIBLE_TO_TEST(B, T1, T2)	\
	static_assert(B == hamon::convertible_to<T1, T2>::value, "");	\
	static_assert(B == hamon::convertible_to_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace convertible_to_test
{

HAMON_CONVERTIBLE_TO_TEST(true,  int, int);
HAMON_CONVERTIBLE_TO_TEST(true,  int&, int);
HAMON_CONVERTIBLE_TO_TEST(false, int, int&);
HAMON_CONVERTIBLE_TO_TEST(true,  int, const int&);
HAMON_CONVERTIBLE_TO_TEST(false, int&&, int&);
HAMON_CONVERTIBLE_TO_TEST(true,  int&&, const int&);
HAMON_CONVERTIBLE_TO_TEST(true,  const int, int);
HAMON_CONVERTIBLE_TO_TEST(false, const int, int&);
HAMON_CONVERTIBLE_TO_TEST(true,  const int, const int);
HAMON_CONVERTIBLE_TO_TEST(true,  const int, const int&);

HAMON_CONVERTIBLE_TO_TEST(true,  int, float);
HAMON_CONVERTIBLE_TO_TEST(false, int, float&);
HAMON_CONVERTIBLE_TO_TEST(false, int, int*);
HAMON_CONVERTIBLE_TO_TEST(true,  int*, void*);
HAMON_CONVERTIBLE_TO_TEST(true,  int*, const void*);
HAMON_CONVERTIBLE_TO_TEST(false, const int*, void*);
HAMON_CONVERTIBLE_TO_TEST(false, int, void);

struct A { };
HAMON_CONVERTIBLE_TO_TEST(true,  A, A);
HAMON_CONVERTIBLE_TO_TEST(true,  A, const A);
HAMON_CONVERTIBLE_TO_TEST(true,  A const, const A);
HAMON_CONVERTIBLE_TO_TEST(false, volatile A, const A);
HAMON_CONVERTIBLE_TO_TEST(false, volatile A, const volatile A&);
HAMON_CONVERTIBLE_TO_TEST(true,  volatile A&, const volatile A&);

struct B : A { };
HAMON_CONVERTIBLE_TO_TEST(false, A, B);
HAMON_CONVERTIBLE_TO_TEST(true,  B, A);
HAMON_CONVERTIBLE_TO_TEST(true,  const B, A);
HAMON_CONVERTIBLE_TO_TEST(true,  B, const A);
HAMON_CONVERTIBLE_TO_TEST(true,  B, const A&);
HAMON_CONVERTIBLE_TO_TEST(false, volatile B, const A);
HAMON_CONVERTIBLE_TO_TEST(false, volatile B, const A&);

struct C : private A { };
HAMON_CONVERTIBLE_TO_TEST(false, A, C);
HAMON_CONVERTIBLE_TO_TEST(false, C, A);

struct D : A { };
struct E : B, D { };
HAMON_CONVERTIBLE_TO_TEST(false, A, E);
HAMON_CONVERTIBLE_TO_TEST(false, E, A);

struct F
{
	F(A) { }
	F(C&&) { }
};
HAMON_CONVERTIBLE_TO_TEST(true,  A, F);
HAMON_CONVERTIBLE_TO_TEST(true,  const A, F);
HAMON_CONVERTIBLE_TO_TEST(true,  C, F);
HAMON_CONVERTIBLE_TO_TEST(false, C&, F);
HAMON_CONVERTIBLE_TO_TEST(false, const C, F);

struct G
{
	operator int() const;
};
HAMON_CONVERTIBLE_TO_TEST(true,  G, int);
HAMON_CONVERTIBLE_TO_TEST(false, int, G);
HAMON_CONVERTIBLE_TO_TEST(true,  G&, int);
HAMON_CONVERTIBLE_TO_TEST(true,  G&&, int);
HAMON_CONVERTIBLE_TO_TEST(false, G*, int);
HAMON_CONVERTIBLE_TO_TEST(false, G, int&);

struct H
{
	explicit operator int() const;
};
HAMON_CONVERTIBLE_TO_TEST(false, H, int);
HAMON_CONVERTIBLE_TO_TEST(false, int, H);
HAMON_CONVERTIBLE_TO_TEST(false, H&, int);
HAMON_CONVERTIBLE_TO_TEST(false, H&&, int);
HAMON_CONVERTIBLE_TO_TEST(false, H*, int);

// Difference between std::is_convertible and std::convertible_to
// https://stackoverflow.com/questions/62644070/differences-between-stdis-convertible-and-stdconvertible-to-in-practice
struct From;
struct To {
	explicit To(From) = delete;
};
struct From {
	operator To();
};
HAMON_CONVERTIBLE_TO_TEST(false, From, To);

}	// namespace convertible_to_test

}	// namespace hamon_concepts_test

#undef HAMON_CONVERTIBLE_TO_TEST
