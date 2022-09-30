/**
 *	@file	unit_test_concepts_relation.cpp
 *
 *	@brief	relation のテスト
 */

#include <hamon/concepts/relation.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RELATION_TEST(B, ...)	\
	static_assert(B == hamon::relation<__VA_ARGS__>, "");	\
	static_assert(B == hamon::relation_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RELATION_TEST(B, ...) \
	static_assert(B == hamon::relation<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::relation_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace relation_test
{

HAMON_RELATION_TEST(false, bool, void, void);
HAMON_RELATION_TEST(false, bool(), void, void);
HAMON_RELATION_TEST(false, bool(*)(), void, void);
HAMON_RELATION_TEST(false, bool(&)(int, int), void, void);
HAMON_RELATION_TEST(false, bool(), int, int);
HAMON_RELATION_TEST(false, bool() const, int, int);

HAMON_RELATION_TEST(true,  bool(*)(int, int), short, long);
HAMON_RELATION_TEST(true,  bool(&)(const void*, const void*), char[2], int*);

HAMON_RELATION_TEST(false, bool& (const long*, short), long*, char);

struct A;
HAMON_RELATION_TEST(false, int A::*, const A&, const A&);
HAMON_RELATION_TEST(false, void (A::*)(long&), const A*, long&);
HAMON_RELATION_TEST(false, void (A::*)(long&) const, A*, long&);
HAMON_RELATION_TEST(true,  long (A::*)(A*) const, A*, A*);

struct F
{
	void operator()(long, long) const;
	bool& operator()(int, const int&) const;
};
HAMON_RELATION_TEST(false, F, long, long);
HAMON_RELATION_TEST(true,  F&, int, int);
HAMON_RELATION_TEST(true,  const F&, const int, const int);

}	// namespace relation_test

}	// namespace hamon_concepts_test

#undef HAMON_RELATION_TEST
