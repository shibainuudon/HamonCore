/**
 *	@file	unit_test_concepts_class_or_enum.cpp
 *
 *	@brief	class_or_enum のテスト
 */

#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CLASS_OR_ENUM_TEST(B, T)	\
	static_assert(B == hamon::detail::class_or_enum<T>, "");	\
	static_assert(B == hamon::detail::class_or_enum_t<T>::value, "")
#else
#  define HAMON_CLASS_OR_ENUM_TEST(B, T) \
	static_assert(B == hamon::detail::class_or_enum<T>::value, "");	\
	static_assert(B == hamon::detail::class_or_enum_t<T>::value, "")
#endif

namespace hamon_concepts_test
{

namespace class_or_enum_test
{

// signed integer types
HAMON_CLASS_OR_ENUM_TEST(false,  signed char);
HAMON_CLASS_OR_ENUM_TEST(false,  signed short);
HAMON_CLASS_OR_ENUM_TEST(false,  signed int);
HAMON_CLASS_OR_ENUM_TEST(false,  signed long);
HAMON_CLASS_OR_ENUM_TEST(false,  signed long long);

// unsigned integer types
HAMON_CLASS_OR_ENUM_TEST(false,  unsigned char);
HAMON_CLASS_OR_ENUM_TEST(false,  unsigned short);
HAMON_CLASS_OR_ENUM_TEST(false,  unsigned int);
HAMON_CLASS_OR_ENUM_TEST(false,  unsigned long);
HAMON_CLASS_OR_ENUM_TEST(false,  unsigned long long);

// other class_or_enum types
HAMON_CLASS_OR_ENUM_TEST(false,  bool);
HAMON_CLASS_OR_ENUM_TEST(false,  char);
HAMON_CLASS_OR_ENUM_TEST(false,  wchar_t);
#if defined(HAMON_HAS_CXX11_CHAR16_T)
HAMON_CLASS_OR_ENUM_TEST(false,  char16_t);
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
HAMON_CLASS_OR_ENUM_TEST(false,  char32_t);
#endif
#if 0//defined(HAMON_HAS_CXX20_CHAR8_T)
HAMON_CLASS_OR_ENUM_TEST(false,  char8_t);
#endif

HAMON_CLASS_OR_ENUM_TEST(false, void);
HAMON_CLASS_OR_ENUM_TEST(false, float);
HAMON_CLASS_OR_ENUM_TEST(false, int*);
HAMON_CLASS_OR_ENUM_TEST(false, int&);
HAMON_CLASS_OR_ENUM_TEST(false, int&&);
HAMON_CLASS_OR_ENUM_TEST(false, const int&);
HAMON_CLASS_OR_ENUM_TEST(false, int[]);
HAMON_CLASS_OR_ENUM_TEST(false, int[2]);
HAMON_CLASS_OR_ENUM_TEST(false, int());
HAMON_CLASS_OR_ENUM_TEST(false, int(*)());
HAMON_CLASS_OR_ENUM_TEST(false, int(&)());

enum E { };
HAMON_CLASS_OR_ENUM_TEST(true, E);
enum class CE { };
HAMON_CLASS_OR_ENUM_TEST(true, CE);
struct A { };
HAMON_CLASS_OR_ENUM_TEST(true, A);
union B { };
HAMON_CLASS_OR_ENUM_TEST(true, B);

}	// namespace class_or_enum_test

}	// namespace hamon_concepts_test

#undef HAMON_CLASS_OR_ENUM_TEST
