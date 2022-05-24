/**
 *	@file	unit_test_concepts_signed_integral.cpp
 *
 *	@brief	signed_integral のテスト
 */

#include <hamon/concepts/signed_integral.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_SIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == hamon::signed_integral<T>, "");	\
	static_assert(B == hamon::signed_integral_t<T>::value, "")
#else
#  define HAMON_SIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == hamon::signed_integral<T>::value, "");	\
	static_assert(B == hamon::signed_integral_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace signed_integral_test
{

// signed integer types
HAMON_SIGNED_INTEGRAL_TEST(true,  signed char);
HAMON_SIGNED_INTEGRAL_TEST(true,  signed short);
HAMON_SIGNED_INTEGRAL_TEST(true,  signed int);
HAMON_SIGNED_INTEGRAL_TEST(true,  signed long);
HAMON_SIGNED_INTEGRAL_TEST(true,  signed long long);

// unsigned integer types
HAMON_SIGNED_INTEGRAL_TEST(false, unsigned char);
HAMON_SIGNED_INTEGRAL_TEST(false, unsigned short);
HAMON_SIGNED_INTEGRAL_TEST(false, unsigned int);
HAMON_SIGNED_INTEGRAL_TEST(false, unsigned long);
HAMON_SIGNED_INTEGRAL_TEST(false, unsigned long long);

// other integral types
HAMON_SIGNED_INTEGRAL_TEST(false, bool);
#if CHAR_MIN < 0
HAMON_SIGNED_INTEGRAL_TEST(true,  char);
#else
HAMON_SIGNED_INTEGRAL_TEST(false, char);
#endif
#if WCHAR_MIN < 0
HAMON_SIGNED_INTEGRAL_TEST(true,  wchar_t);
#else
HAMON_SIGNED_INTEGRAL_TEST(false, wchar_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_SIGNED_INTEGRAL_TEST(false, char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_SIGNED_INTEGRAL_TEST(false, char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_SIGNED_INTEGRAL_TEST(false, char8_t);
#endif

HAMON_SIGNED_INTEGRAL_TEST(false, void);
HAMON_SIGNED_INTEGRAL_TEST(false, float);
HAMON_SIGNED_INTEGRAL_TEST(false, int&);
HAMON_SIGNED_INTEGRAL_TEST(false, int&);
HAMON_SIGNED_INTEGRAL_TEST(false, int&&);
HAMON_SIGNED_INTEGRAL_TEST(false, const int&);
HAMON_SIGNED_INTEGRAL_TEST(false, int[]);
HAMON_SIGNED_INTEGRAL_TEST(false, int[2]);
HAMON_SIGNED_INTEGRAL_TEST(false, int());
HAMON_SIGNED_INTEGRAL_TEST(false, int(*)());
HAMON_SIGNED_INTEGRAL_TEST(false, int(&)());

enum E { };
HAMON_SIGNED_INTEGRAL_TEST(false, E);
enum class CE { };
HAMON_SIGNED_INTEGRAL_TEST(false, CE);
struct A { };
HAMON_SIGNED_INTEGRAL_TEST(false, A);
union B { };
HAMON_SIGNED_INTEGRAL_TEST(false, B);

}	// namespace signed_integral_test

}	// namespace hamon_concepts_test

#undef HAMON_SIGNED_INTEGRAL_TEST
