/**
 *	@file	unit_test_concepts_cpp17_default_constructible.cpp
 *
 *	@brief	cpp17_default_constructible のテスト
 */

#include <hamon/concepts/detail/cpp17_default_constructible.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wunused-private-field")

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_default_constructible<__VA_ARGS__>, "");	\
	static_assert(B == hamon::detail::cpp17_default_constructible_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(B, ...)	\
	static_assert(B == hamon::detail::cpp17_default_constructible<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::detail::cpp17_default_constructible_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace cpp17_default_constructible_test
{

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, void);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, void const);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, void       volatile);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, void const volatile);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  void               *);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  void const         *);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  void       volatile*);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  void const volatile*);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int       volatile);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int               *);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const         *);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int       volatile*);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const volatile*);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               &);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         &);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile&);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile&);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               &&);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         &&);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile&&);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile&&);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               []);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         []);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile[]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int               (*)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const         (*)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int       volatile(*)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const volatile(*)[]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               (&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         (&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile(&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile(&)[]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               (&&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         (&&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile(&&)[]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile(&&)[]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               [2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         [2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile[2]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int               (*)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const         (*)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int       volatile(*)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int const volatile(*)[2]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               (&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         (&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile(&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile(&)[2]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int               (&&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const         (&&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int       volatile(&&)[2]);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int const volatile(&&)[2]);

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int());
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  int(*)());
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, int(&)());

HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  char);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  long);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  float);
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  double);

enum E { };
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  E);
enum class CE { };
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  CE);
struct A { };
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  A);
union B { };
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  B);

struct C
{
	C(void* = nullptr) { }
	~C() noexcept(false) { }
};
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  C);	// different from `default_initializable_t`

class D
{
public:
	D() { }
};
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  D);

class S1
{
public:
	S1() { }

private:
	int n;
};
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  S1);

class S2
{
public:
	S2(int) { }

private:
	int n;
};
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(false, S2);

class S3
{
	int n;

	virtual int f() { return n; }
};
HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST(true,  S3);

}	// namespace cpp17_default_constructible_test

}	// namespace hamon_concepts_test

#undef HAMON_CPP17_DEFAULT_CONSTRUCTIBLE_TEST

HAMON_WARNING_POP()
