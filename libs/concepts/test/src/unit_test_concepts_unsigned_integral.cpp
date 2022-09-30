/**
 *	@file	unit_test_concepts_unsigned_integral.cpp
 *
 *	@brief	unsigned_integral のテスト
 */

#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/config.hpp>
#include <cstdint>	// WCHAR_MIN
#include <climits>	// CHAR_MIN

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_UNSIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == hamon::unsigned_integral<T>, "");	\
	static_assert(B == hamon::unsigned_integral_t<T>::value, "")
#else
#  define HAMON_UNSIGNED_INTEGRAL_TEST(B, T)	\
	static_assert(B == hamon::unsigned_integral<T>::value, "");	\
	static_assert(B == hamon::unsigned_integral_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace unsigned_integral_test
{

// unsigned integer types
HAMON_UNSIGNED_INTEGRAL_TEST(true,  unsigned char);
HAMON_UNSIGNED_INTEGRAL_TEST(true,  unsigned short);
HAMON_UNSIGNED_INTEGRAL_TEST(true,  unsigned int);
HAMON_UNSIGNED_INTEGRAL_TEST(true,  unsigned long);
HAMON_UNSIGNED_INTEGRAL_TEST(true,  unsigned long long);

// signed integer types
HAMON_UNSIGNED_INTEGRAL_TEST(false, signed char);
HAMON_UNSIGNED_INTEGRAL_TEST(false, signed short);
HAMON_UNSIGNED_INTEGRAL_TEST(false, signed int);
HAMON_UNSIGNED_INTEGRAL_TEST(false, signed long);
HAMON_UNSIGNED_INTEGRAL_TEST(false, signed long long);

// other integral types
HAMON_UNSIGNED_INTEGRAL_TEST(true,  bool);
#if CHAR_MIN < 0
HAMON_UNSIGNED_INTEGRAL_TEST(false, char);
#else
HAMON_UNSIGNED_INTEGRAL_TEST(true,  char);
#endif
#if WCHAR_MIN < 0
HAMON_UNSIGNED_INTEGRAL_TEST(false, wchar_t);
#else
HAMON_UNSIGNED_INTEGRAL_TEST(true,  wchar_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_UNSIGNED_INTEGRAL_TEST(true,  char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_UNSIGNED_INTEGRAL_TEST(true,  char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_UNSIGNED_INTEGRAL_TEST(true,  char8_t);
#endif

HAMON_UNSIGNED_INTEGRAL_TEST(false, void);
HAMON_UNSIGNED_INTEGRAL_TEST(false, float);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned&);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned&);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned&&);
HAMON_UNSIGNED_INTEGRAL_TEST(false, const unsigned&);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned[]);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned[2]);
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned());
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned(*)());
HAMON_UNSIGNED_INTEGRAL_TEST(false, unsigned(&)());

enum E { };
HAMON_UNSIGNED_INTEGRAL_TEST(false, E);
enum class CE { };
HAMON_UNSIGNED_INTEGRAL_TEST(false, CE);
struct A { };
HAMON_UNSIGNED_INTEGRAL_TEST(false, A);
union B { };
HAMON_UNSIGNED_INTEGRAL_TEST(false, B);

}	// namespace unsigned_integral_test

}	// namespace hamon_concepts_test

#undef HAMON_UNSIGNED_INTEGRAL_TEST
