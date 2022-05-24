/**
 *	@file	unit_test_concepts_assignable_from.cpp
 *
 *	@brief	assignable_from のテスト
 */

#include <hamon/concepts/assignable_from.hpp>
#include <hamon/config.hpp>
#include <cstddef>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_ASSIGNABLE_FROM_TEST(B, T1, T2)	\
	static_assert(B == hamon::assignable_from<T1, T2>, "");	\
	static_assert(B == hamon::assignable_from_t<T1, T2>::value, "")
#else
#  define HAMON_ASSIGNABLE_FROM_TEST(B, T1, T2)	\
	static_assert(B == hamon::assignable_from<T1, T2>::value, "");	\
	static_assert(B == hamon::assignable_from_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace assignable_from_test
{

HAMON_ASSIGNABLE_FROM_TEST(false, void, void);
HAMON_ASSIGNABLE_FROM_TEST(false, void*, int*);
HAMON_ASSIGNABLE_FROM_TEST(true,  void*&, int*);
HAMON_ASSIGNABLE_FROM_TEST(false, void*&, const int*);
HAMON_ASSIGNABLE_FROM_TEST(true,  const void*&, const int*);
HAMON_ASSIGNABLE_FROM_TEST(false, char, char);
HAMON_ASSIGNABLE_FROM_TEST(true,  char&, char);
HAMON_ASSIGNABLE_FROM_TEST(false, float, float);
HAMON_ASSIGNABLE_FROM_TEST(true,  float&, double);
HAMON_ASSIGNABLE_FROM_TEST(true,  int*&, int*);
HAMON_ASSIGNABLE_FROM_TEST(true,  int&, int&);
HAMON_ASSIGNABLE_FROM_TEST(true,  int&, int&&);
HAMON_ASSIGNABLE_FROM_TEST(false, int&&, int);
HAMON_ASSIGNABLE_FROM_TEST(false, const int&, int);
HAMON_ASSIGNABLE_FROM_TEST(false, const int&, int&);
HAMON_ASSIGNABLE_FROM_TEST(false, const int&, const int);
HAMON_ASSIGNABLE_FROM_TEST(false, const int&, const int&);
HAMON_ASSIGNABLE_FROM_TEST(false, int(&)[], int(&)[]);
HAMON_ASSIGNABLE_FROM_TEST(false, int(&)[], int);
HAMON_ASSIGNABLE_FROM_TEST(false, int(&)[2], int(&)[2]);
HAMON_ASSIGNABLE_FROM_TEST(false, int(), int());
HAMON_ASSIGNABLE_FROM_TEST(false, int(*)(), int(*)());
HAMON_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(*)());
HAMON_ASSIGNABLE_FROM_TEST(true,  int(*&)(), std::nullptr_t);
#if !(defined(HAMON_MSVC) && (HAMON_MSVC < 1920))
HAMON_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(*)() noexcept);
#endif
HAMON_ASSIGNABLE_FROM_TEST(true,  int(*&)(), int(&)() noexcept);
HAMON_ASSIGNABLE_FROM_TEST(false, int(&)(), std::nullptr_t);
#if !defined(HAMON_MSVC)
HAMON_ASSIGNABLE_FROM_TEST(false, int(&)(), int(&)() noexcept);
#endif

enum E { };
HAMON_ASSIGNABLE_FROM_TEST(false, E, E);
HAMON_ASSIGNABLE_FROM_TEST(true,  E&, E);
HAMON_ASSIGNABLE_FROM_TEST(true,  E&, E&);
HAMON_ASSIGNABLE_FROM_TEST(true,  E&, const E&);
HAMON_ASSIGNABLE_FROM_TEST(false, const E&, const E&);
enum class CE { };
HAMON_ASSIGNABLE_FROM_TEST(false, CE, CE);
HAMON_ASSIGNABLE_FROM_TEST(true,  CE&, CE&);
HAMON_ASSIGNABLE_FROM_TEST(true,  CE&, const CE&);
HAMON_ASSIGNABLE_FROM_TEST(false, const CE&, const CE&);
struct A { };
HAMON_ASSIGNABLE_FROM_TEST(false, A, A);
HAMON_ASSIGNABLE_FROM_TEST(true,  A&, A);
HAMON_ASSIGNABLE_FROM_TEST(false, A, A&);
HAMON_ASSIGNABLE_FROM_TEST(true,  A&, const A&);
union B { };
HAMON_ASSIGNABLE_FROM_TEST(false, B, B);
HAMON_ASSIGNABLE_FROM_TEST(true,  B&, B);
HAMON_ASSIGNABLE_FROM_TEST(false, B, B&);
HAMON_ASSIGNABLE_FROM_TEST(true,  B&, const B&);

struct C
{
	C(int) { }
	C(const C&) { }
	C& operator=(const C&) { return *this; }
	C& operator=(int) { return *this; }
	void operator=(void*) { }
};
HAMON_ASSIGNABLE_FROM_TEST(true,  C&, C);
HAMON_ASSIGNABLE_FROM_TEST(true,  C&, const C&);
HAMON_ASSIGNABLE_FROM_TEST(true,  C&, int);
HAMON_ASSIGNABLE_FROM_TEST(false, C&, void*);
HAMON_ASSIGNABLE_FROM_TEST(false, C&, std::nullptr_t);

}	// namespace assignable_from_test

}	// namespace hamon_concepts_test

#undef HAMON_ASSIGNABLE_FROM_TEST
