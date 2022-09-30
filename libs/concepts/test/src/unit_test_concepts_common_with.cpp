/**
 *	@file	unit_test_concepts_common_with.cpp
 *
 *	@brief	common_with のテスト
 */

#include <hamon/concepts/common_with.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_COMMON_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::common_with<T1, T2>, "");	\
	static_assert(B == hamon::common_with_t<T1, T2>::value, "")
#else
#  define HAMON_COMMON_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::common_with<T1, T2>::value, "");	\
	static_assert(B == hamon::common_with_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace common_with_test
{

HAMON_COMMON_WITH_TEST(true,  int, int);
HAMON_COMMON_WITH_TEST(true,  int, const int);
HAMON_COMMON_WITH_TEST(true,  int&&, const int&);
HAMON_COMMON_WITH_TEST(true,  int&, const int&&);
HAMON_COMMON_WITH_TEST(true,  void, void);
HAMON_COMMON_WITH_TEST(false, int, void);
HAMON_COMMON_WITH_TEST(false, int, int*);
HAMON_COMMON_WITH_TEST(false, int, int());

HAMON_COMMON_WITH_TEST(true,  int, short);
HAMON_COMMON_WITH_TEST(true,  short, int);
HAMON_COMMON_WITH_TEST(true,  void*, const int*);

struct A { A(int) { } };
HAMON_COMMON_WITH_TEST(true,  A, int);

struct B { };
HAMON_COMMON_WITH_TEST(false, A, B);

struct C { C(const A&) { } };
HAMON_COMMON_WITH_TEST(true,  A, C);
HAMON_COMMON_WITH_TEST(true,  A, const C);
HAMON_COMMON_WITH_TEST(true,  const A, C);
HAMON_COMMON_WITH_TEST(true,  const A, const C);

struct D;
struct E { E(const D&) { } };
struct D { D(const E&) { } };
HAMON_COMMON_WITH_TEST(false, D, E); // ambiguous conversion

struct F { };
struct G { };
struct H {
	H(const F&) { }
	H(const G&) { }
};

}	// namespace common_with_test

}	// namespace hamon_concepts_test

namespace HAMON_COMMON_TYPE_NAMESPACE
{

template<>
struct common_type<
	hamon_concepts_test::common_with_test::F,
	hamon_concepts_test::common_with_test::G
>
{
	using type = hamon_concepts_test::common_with_test::H;
};

template<>
struct common_type<
	hamon_concepts_test::common_with_test::G,
	hamon_concepts_test::common_with_test::F
>
{
	using type = hamon_concepts_test::common_with_test::H;
};

}	// namespace hamon

namespace hamon_concepts_test
{

namespace common_with_test
{

HAMON_COMMON_WITH_TEST(true,  F, G);
HAMON_COMMON_WITH_TEST(true,  F, const G);
HAMON_COMMON_WITH_TEST(true,  const F, G);
HAMON_COMMON_WITH_TEST(true,  const F, const G);

struct Base { };
struct Derived : Base { };
HAMON_COMMON_WITH_TEST(true,  Derived, Base);
HAMON_COMMON_WITH_TEST(true,  Derived*, Base*);

}	// namespace common_with_test

}	// namespace hamon_concepts_test

#undef HAMON_COMMON_WITH_TEST
