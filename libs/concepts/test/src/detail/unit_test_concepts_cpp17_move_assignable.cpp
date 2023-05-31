/**
 *	@file	unit_test_concepts_cpp17_move_assignable.cpp
 *
 *	@brief	cpp17_move_assignable のテスト
 */

#include <hamon/concepts/detail/cpp17_move_assignable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_MOVE_ASSIGNABLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_move_assignable<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_move_assignable_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_MOVE_ASSIGNABLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_move_assignable<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_move_assignable_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_move_assignable_test
{

HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, void);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, void const);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, void       volatile);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, void const volatile);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  void               *);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  void const         *);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  void       volatile*);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  void const volatile*);

HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int       volatile);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const volatile);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int               *);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int const         *);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int       volatile*);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int const volatile*);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int               &);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const         &);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int       volatile&);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const volatile&);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int               &&);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const         &&);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int       volatile&&);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int const volatile&&);

HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int[]);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int[2]);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int(*)[2]);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int(&)[2]);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int(&&)[2]);
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int());
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  int(*)());
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, int(&)());
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, void());

enum E { };
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  E);
enum class CE { };
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  CE);
struct A { };
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  A);
union B { };
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  B);

struct S1
{
	S1& operator=(S1 const&);
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  S1);

struct S2
{
	S2& operator=(S2 &&);
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  S2);

struct S3
{
	S3& operator=(S3 const&) = delete;
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, S3);

struct S4
{
	S4& operator=(S4 &&) = delete;
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, S4);

struct S5
{
	S5& operator=(S5 const&) = delete;
	S5& operator=(S5 &&);
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  S5);

struct S6
{
	S6& operator=(S6 const&);
	S6& operator=(S6 &&) = delete;
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, S6);

struct S7
{
	void operator=(S7 const&);
	S7& operator=(S7 &&);
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(true,  S7);

struct S8
{
	S8& operator=(S8 const&);
	void operator=(S8 &&);
};
HAMON_CPP17_MOVE_ASSIGNABLE_TEST(false, S8);

}	// namespace cpp17_move_assignable_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_MOVE_ASSIGNABLE_TEST
