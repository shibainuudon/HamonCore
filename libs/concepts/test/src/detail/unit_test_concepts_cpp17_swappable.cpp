/**
 *	@file	unit_test_concepts_cpp17_swappable.cpp
 *
 *	@brief	cpp17_swappable のテスト
 */

#include <hamon/concepts/detail/cpp17_swappable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_swappable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_swappable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_SWAPPABLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_swappable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_swappable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_swappable_test
{

HAMON_CPP17_SWAPPABLE_TEST(false, void);
HAMON_CPP17_SWAPPABLE_TEST(false, void const);
HAMON_CPP17_SWAPPABLE_TEST(false, void       volatile);
HAMON_CPP17_SWAPPABLE_TEST(false, void const volatile);

HAMON_CPP17_SWAPPABLE_TEST(true,  void               *);
HAMON_CPP17_SWAPPABLE_TEST(true,  void const         *);
HAMON_CPP17_SWAPPABLE_TEST(true,  void       volatile*);
HAMON_CPP17_SWAPPABLE_TEST(true,  void const volatile*);

HAMON_CPP17_SWAPPABLE_TEST(true,  int);
HAMON_CPP17_SWAPPABLE_TEST(false, int const);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile);
HAMON_CPP17_SWAPPABLE_TEST(false,  int const volatile);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               *);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const         *);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile*);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const volatile*);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               &);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         &);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile&);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile&);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               &&);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         &&);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile&&);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile&&);

HAMON_CPP17_SWAPPABLE_TEST(false, int               []);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         []);
HAMON_CPP17_SWAPPABLE_TEST(false, int       volatile[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile[]);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               (*)[]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const         (*)[]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile(*)[]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const volatile(*)[]);

HAMON_CPP17_SWAPPABLE_TEST(false, int               (&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         (&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int       volatile(&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile(&)[]);

HAMON_CPP17_SWAPPABLE_TEST(false, int               (&&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         (&&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int       volatile(&&)[]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile(&&)[]);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               [2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         [2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile[2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile[2]);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               (*)[2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const         (*)[2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile(*)[2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int const volatile(*)[2]);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               (&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         (&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile(&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile(&)[2]);

HAMON_CPP17_SWAPPABLE_TEST(true,  int               (&&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const         (&&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(true,  int       volatile(&&)[2]);
HAMON_CPP17_SWAPPABLE_TEST(false, int const volatile(&&)[2]);

HAMON_CPP17_SWAPPABLE_TEST(false, int());
HAMON_CPP17_SWAPPABLE_TEST(true,  int(*)());
HAMON_CPP17_SWAPPABLE_TEST(false, int(&)());

HAMON_CPP17_SWAPPABLE_TEST(true,  char);
HAMON_CPP17_SWAPPABLE_TEST(true,  long);
HAMON_CPP17_SWAPPABLE_TEST(true,  float);
HAMON_CPP17_SWAPPABLE_TEST(true,  double);

enum E { };
HAMON_CPP17_SWAPPABLE_TEST(true,  E);
enum class CE { };
HAMON_CPP17_SWAPPABLE_TEST(true,  CE);
struct A { };
HAMON_CPP17_SWAPPABLE_TEST(true,  A);
union B { };
HAMON_CPP17_SWAPPABLE_TEST(true,  B);

struct S1
{
};

void swap(S1&, S1&) = delete;

HAMON_CPP17_SWAPPABLE_TEST(false, S1);

}	// namespace cpp17_swappable_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_SWAPPABLE_TEST
