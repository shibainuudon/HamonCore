/**
 *	@file	unit_test_concepts_arithmetic.cpp
 *
 *	@brief	arithmetic のテスト
 */

#include <hamon/concepts/arithmetic.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_ARITHMETIC_TEST(B, T)	\
	static_assert(B == hamon::arithmetic<T>, "");	\
	static_assert(B == hamon::arithmetic_t<T>::value, "")
#else
#  define HAMON_ARITHMETIC_TEST(B, T) \
	static_assert(B == hamon::arithmetic<T>::value, "");	\
	static_assert(B == hamon::arithmetic_t<T>::value, "")
#endif

#define HAMON_ARITHMETIC_TEST_CV(B, T)			\
	HAMON_ARITHMETIC_TEST(B,                T);	\
	HAMON_ARITHMETIC_TEST(B, const          T);	\
	HAMON_ARITHMETIC_TEST(B,       volatile T);	\
	HAMON_ARITHMETIC_TEST(B, const volatile T)

namespace hamon_concepts_test
{

namespace arithmetic_test
{

// signed integer types
HAMON_ARITHMETIC_TEST_CV(true,  signed char);
HAMON_ARITHMETIC_TEST_CV(true,  signed short);
HAMON_ARITHMETIC_TEST_CV(true,  signed int);
HAMON_ARITHMETIC_TEST_CV(true,  signed long);
HAMON_ARITHMETIC_TEST_CV(true,  signed long long);

// unsigned integer types
HAMON_ARITHMETIC_TEST_CV(true,  unsigned char);
HAMON_ARITHMETIC_TEST_CV(true,  unsigned short);
HAMON_ARITHMETIC_TEST_CV(true,  unsigned int);
HAMON_ARITHMETIC_TEST_CV(true,  unsigned long);
HAMON_ARITHMETIC_TEST_CV(true,  unsigned long long);

// floating point types
HAMON_ARITHMETIC_TEST_CV(true,  float);
HAMON_ARITHMETIC_TEST_CV(true,  double);
HAMON_ARITHMETIC_TEST_CV(true,  long double);

// other arithmetic types
HAMON_ARITHMETIC_TEST_CV(true,  bool);
HAMON_ARITHMETIC_TEST_CV(true,  char);
HAMON_ARITHMETIC_TEST_CV(true,  wchar_t);
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_ARITHMETIC_TEST_CV(true,  char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_ARITHMETIC_TEST_CV(true,  char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_ARITHMETIC_TEST_CV(true,  char8_t);
#endif

// not arithmetic types
HAMON_ARITHMETIC_TEST_CV(false, void);
HAMON_ARITHMETIC_TEST_CV(false, int*);
HAMON_ARITHMETIC_TEST_CV(false, int&);
HAMON_ARITHMETIC_TEST_CV(false, int&&);
HAMON_ARITHMETIC_TEST_CV(false, int[]);
HAMON_ARITHMETIC_TEST_CV(false, int[2]);
HAMON_ARITHMETIC_TEST(false, int());
HAMON_ARITHMETIC_TEST(false, int(*)());
HAMON_ARITHMETIC_TEST(false, int(&)());

enum E { };
HAMON_ARITHMETIC_TEST_CV(false, E);
enum class CE { };
HAMON_ARITHMETIC_TEST_CV(false, CE);
struct A { };
HAMON_ARITHMETIC_TEST_CV(false, A);
union B { };
HAMON_ARITHMETIC_TEST_CV(false, B);

}	// namespace arithmetic_test

}	// namespace hamon_concepts_test

#undef HAMON_ARITHMETIC_TEST
#undef HAMON_ARITHMETIC_TEST_CV
