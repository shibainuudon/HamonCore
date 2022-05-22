/**
 *	@file	unit_test_concepts_integral.cpp
 *
 *	@brief	integral のテスト
 */

#include <hamon/concepts/integral.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INTEGRAL_TEST(B, T)	\
	static_assert(B == hamon::integral<T>, "");	\
	static_assert(B == hamon::integral_t<T>::value, "")
#else
#  define HAMON_INTEGRAL_TEST(B, T) \
	static_assert(B == hamon::integral<T>::value, "");	\
	static_assert(B == hamon::integral_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace integral_test
{

// signed integer types
HAMON_INTEGRAL_TEST(true,  signed char);
HAMON_INTEGRAL_TEST(true,  signed short);
HAMON_INTEGRAL_TEST(true,  signed int);
HAMON_INTEGRAL_TEST(true,  signed long);
HAMON_INTEGRAL_TEST(true,  signed long long);

// unsigned integer types
HAMON_INTEGRAL_TEST(true,  unsigned char);
HAMON_INTEGRAL_TEST(true,  unsigned short);
HAMON_INTEGRAL_TEST(true,  unsigned int);
HAMON_INTEGRAL_TEST(true,  unsigned long);
HAMON_INTEGRAL_TEST(true,  unsigned long long);

// other integral types
HAMON_INTEGRAL_TEST(true,  bool);
HAMON_INTEGRAL_TEST(true,  char);
HAMON_INTEGRAL_TEST(true,  wchar_t);
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_INTEGRAL_TEST(true,  char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_INTEGRAL_TEST(true,  char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_INTEGRAL_TEST(true,  char8_t);
#endif

HAMON_INTEGRAL_TEST(false, void);
HAMON_INTEGRAL_TEST(false, float);
HAMON_INTEGRAL_TEST(false, int*);
HAMON_INTEGRAL_TEST(false, int&);
HAMON_INTEGRAL_TEST(false, int&&);
HAMON_INTEGRAL_TEST(false, const int&);
HAMON_INTEGRAL_TEST(false, int[]);
HAMON_INTEGRAL_TEST(false, int[2]);
HAMON_INTEGRAL_TEST(false, int());
HAMON_INTEGRAL_TEST(false, int(*)());
HAMON_INTEGRAL_TEST(false, int(&)());

enum E { };
HAMON_INTEGRAL_TEST(false, E);
enum class CE { };
HAMON_INTEGRAL_TEST(false, CE);
struct A { };
HAMON_INTEGRAL_TEST(false, A);
union B { };
HAMON_INTEGRAL_TEST(false, B);

}	// namespace integral_test

}	// namespace hamon_concepts_test

#undef HAMON_INTEGRAL_TEST
