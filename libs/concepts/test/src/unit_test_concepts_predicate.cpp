/**
 *	@file	unit_test_concepts_predicate.cpp
 *
 *	@brief	predicate のテスト
 */

#include <hamon/concepts/predicate.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_PREDICATE_TEST(B, ...)	\
	static_assert(B == hamon::predicate<__VA_ARGS__>, "");	\
	static_assert(B == hamon::predicate_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_PREDICATE_TEST(B, ...) \
	static_assert(B == hamon::predicate<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::predicate_t<__VA_ARGS__>::value, "")
#endif

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_CLANG("-Wunneeded-internal-declaration");

namespace hamon_concepts_test
{

namespace predicate_test
{

bool func1(int);
int  func2();
int* func3(int, int);
void func4(int);
auto lambda1 = [](int a) { return a < 10; };

HAMON_PREDICATE_TEST(false, decltype(func1));
HAMON_PREDICATE_TEST(true,  decltype(func1), int);
HAMON_PREDICATE_TEST(true,  decltype(func1), float);
HAMON_PREDICATE_TEST(false, decltype(func1), int, int);

HAMON_PREDICATE_TEST(true,  decltype(func2));
HAMON_PREDICATE_TEST(false, decltype(func2), int);
HAMON_PREDICATE_TEST(false, decltype(func2), float);
HAMON_PREDICATE_TEST(false, decltype(func2), int, int);

HAMON_PREDICATE_TEST(false, decltype(func3));
HAMON_PREDICATE_TEST(false, decltype(func3), int);
HAMON_PREDICATE_TEST(false, decltype(func3), float);
HAMON_PREDICATE_TEST(true,  decltype(func3), int, int);

HAMON_PREDICATE_TEST(false, decltype(func4));
HAMON_PREDICATE_TEST(false, decltype(func4), int);
HAMON_PREDICATE_TEST(false, decltype(func4), float);
HAMON_PREDICATE_TEST(false, decltype(func4), int, int);

HAMON_PREDICATE_TEST(false, decltype(lambda1));
HAMON_PREDICATE_TEST(true,  decltype(lambda1), int);
HAMON_PREDICATE_TEST(true,  decltype(lambda1), float);
HAMON_PREDICATE_TEST(false, decltype(lambda1), int, int);

HAMON_PREDICATE_TEST(true,  bool(*)());
HAMON_PREDICATE_TEST(false, bool(*)(), int);
HAMON_PREDICATE_TEST(false, bool(*)(), int, int);
HAMON_PREDICATE_TEST(false, bool(*)(int));
HAMON_PREDICATE_TEST(true,  bool(*)(int), int);
HAMON_PREDICATE_TEST(false, bool(*)(int), int, int);
HAMON_PREDICATE_TEST(false, bool(*)(int, int));
HAMON_PREDICATE_TEST(false, bool(*)(int, int), int);
HAMON_PREDICATE_TEST(true,  bool(*)(int, int), int, int);

struct A
{
	operator bool() const;
};
struct B
{
	explicit operator bool() const;
};
struct C
{
	operator bool() const;
	bool operator!() const;
};
struct D
{
	operator bool() const = delete;
	bool operator!() const;
};
struct E
{
	operator bool() const;
	bool operator!() const = delete;
};

HAMON_PREDICATE_TEST(true,  A(*)());
HAMON_PREDICATE_TEST(false, B(*)());
HAMON_PREDICATE_TEST(true,  C(*)());
HAMON_PREDICATE_TEST(false, D(*)());
HAMON_PREDICATE_TEST(false, E(*)());

struct Predicate0
{
	bool operator()() const { return true;}
};
struct Predicate1
{
	bool operator()(int n) const { return n < 10;}
};
struct Predicate2
{
	bool operator()(int n, int) const { return n < 10;}
};

struct NotPredicate
{
	void operator()(int) {}
	void operator()(int, int) {}
};

HAMON_PREDICATE_TEST(true,  Predicate0);
HAMON_PREDICATE_TEST(false, Predicate0, int);
HAMON_PREDICATE_TEST(false, Predicate0, float);
HAMON_PREDICATE_TEST(false, Predicate0, int, int);

HAMON_PREDICATE_TEST(false, Predicate1);
HAMON_PREDICATE_TEST(true,  Predicate1, int);
HAMON_PREDICATE_TEST(true,  Predicate1, float);
HAMON_PREDICATE_TEST(false, Predicate1, int, int);

HAMON_PREDICATE_TEST(false, Predicate2);
HAMON_PREDICATE_TEST(false, Predicate2, int);
HAMON_PREDICATE_TEST(false, Predicate2, float);
HAMON_PREDICATE_TEST(true,  Predicate2, int, int);

HAMON_PREDICATE_TEST(false, NotPredicate);
HAMON_PREDICATE_TEST(false, NotPredicate, int);
HAMON_PREDICATE_TEST(false, NotPredicate, float);
HAMON_PREDICATE_TEST(false, NotPredicate, int, int);

}	// namespace predicate_test

}	// namespace hamon_concepts_test

HAMON_WARNING_POP();

#undef HAMON_PREDICATE_TEST
