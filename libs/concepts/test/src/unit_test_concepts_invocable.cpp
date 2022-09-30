/**
 *	@file	unit_test_concepts_invocable.cpp
 *
 *	@brief	invocable のテスト
 */

#include <hamon/concepts/invocable.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_INVOCABLE_TEST(B, ...)	\
	static_assert(B == hamon::invocable<__VA_ARGS__>, " ");	\
	static_assert(B == hamon::invocable_t<__VA_ARGS__>::value, " ")
#else
#  define HAMON_INVOCABLE_TEST(B, ...) \
	static_assert(B == hamon::invocable<__VA_ARGS__>::value, " ");	\
	static_assert(B == hamon::invocable_t<__VA_ARGS__>::value, " ")
#endif

namespace hamon_concepts_test
{

namespace invocable_test
{

HAMON_INVOCABLE_TEST(false, int);
HAMON_INVOCABLE_TEST(true,  int());
HAMON_INVOCABLE_TEST(true,  int(*)());
HAMON_INVOCABLE_TEST(true,  int(&)());
HAMON_INVOCABLE_TEST(false, int(), int);
HAMON_INVOCABLE_TEST(false, int() const);

HAMON_INVOCABLE_TEST(true,  int(const long*, short), long*, char);

struct A;
HAMON_INVOCABLE_TEST(true,  int A::*, const A&);
HAMON_INVOCABLE_TEST(false, void (A::*)(long&), const A*, long&);
HAMON_INVOCABLE_TEST(true,  void (A::*)(long&) const, A*, long&);

struct F
{
	void operator()() const;
	void operator()(int);
};
HAMON_INVOCABLE_TEST(true,  F);
HAMON_INVOCABLE_TEST(true,  F, int);
HAMON_INVOCABLE_TEST(true,  const F&);
HAMON_INVOCABLE_TEST(false, const F&, int);

}	// namespace invocable_test

}	// namespace hamon_concepts_test

#undef HAMON_INVOCABLE_TEST
