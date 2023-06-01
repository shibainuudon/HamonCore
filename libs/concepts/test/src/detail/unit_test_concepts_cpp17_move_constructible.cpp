/**
 *	@file	unit_test_concepts_cpp17_move_constructible.cpp
 *
 *	@brief	cpp17_move_constructible のテスト
 */

#include <hamon/concepts/detail/cpp17_move_constructible.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_move_constructible<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_move_constructible_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_move_constructible<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_move_constructible_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_move_constructible_test
{

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, void);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, void const);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, void       volatile);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, void const volatile);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  void               *);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  void const         *);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  void       volatile*);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  void const volatile*);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               *);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         *);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile*);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile*);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               &);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         &);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile&);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile&);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               &&);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         &&);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile&&);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile&&);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int               []);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int const         []);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int       volatile[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int const volatile[]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (*)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (*)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(*)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(*)[]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(&)[]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (&&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (&&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(&&)[]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(&&)[]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int               [2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int const         [2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int       volatile[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int const volatile[2]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (*)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (*)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(*)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(*)[2]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(&)[2]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int               (&&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const         (&&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int       volatile(&&)[2]);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int const volatile(&&)[2]);

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, int());
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int(*)());
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  int(&)());

HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  char);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  long);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  float);
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  double);

enum E { };
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  B);

struct S1
{
	S1(S1 const&){}
	S1(S1 &&){}
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  S1);

struct S2
{
	S2(S2 &&){}
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  S2);

struct S3
{
	S3(S3 const&){}
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  S3);

struct S4
{
	S4(S4 const&) = delete;
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, S4);

struct S5
{
	S5(S5 &&) = delete;
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, S5);

struct S6
{
	S6(S6 const&) = delete;
	S6(S6 &&){}
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(true,  S6);

struct S7
{
	S7(S7 const&){}
	S7(S7 &&) = delete;
};
HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST(false, S7);

}	// namespace cpp17_move_constructible_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_MOVE_CONSTRUCTIBLE_TEST
