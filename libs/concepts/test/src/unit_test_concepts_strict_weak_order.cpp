/**
 *	@file	unit_test_concepts_strict_weak_order.cpp
 *
 *	@brief	strict_weak_order のテスト
 */

#include <hamon/concepts/strict_weak_order.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_STRICT_WEAK_ORDER_TEST(B, ...)	\
	static_assert(B == hamon::strict_weak_order<__VA_ARGS__>, "");	\
	static_assert(B == hamon::strict_weak_order_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_STRICT_WEAK_ORDER_TEST(B, ...) \
	static_assert(B == hamon::strict_weak_order<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::strict_weak_order_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace strict_weak_order_test
{

HAMON_STRICT_WEAK_ORDER_TEST(false, bool, void, void);
HAMON_STRICT_WEAK_ORDER_TEST(false, bool(), void, void);
HAMON_STRICT_WEAK_ORDER_TEST(false, bool(*)(), void, void);
HAMON_STRICT_WEAK_ORDER_TEST(false, bool(&)(int, int), void, void);
HAMON_STRICT_WEAK_ORDER_TEST(false, bool(), int, int);
HAMON_STRICT_WEAK_ORDER_TEST(false, bool() const, int, int);

HAMON_STRICT_WEAK_ORDER_TEST(true,  bool(*)(int, int), short, long);
HAMON_STRICT_WEAK_ORDER_TEST(true,  bool(&)(const void*, const void*), char[2], int*);

HAMON_STRICT_WEAK_ORDER_TEST(false, bool& (const long*, short), long*, char);

struct A;
HAMON_STRICT_WEAK_ORDER_TEST(false, int A::*, const A&, const A&);
HAMON_STRICT_WEAK_ORDER_TEST(false, void (A::*)(long&), const A*, long&);
HAMON_STRICT_WEAK_ORDER_TEST(false, void (A::*)(long&) const, A*, long&);
HAMON_STRICT_WEAK_ORDER_TEST(true,  long (A::*)(A*) const, A*, A*);

struct F
{
	void operator()(long, long) const;
	bool& operator()(int, const int&) const;
};
HAMON_STRICT_WEAK_ORDER_TEST(false, F, long, long);
HAMON_STRICT_WEAK_ORDER_TEST(true,  F&, int, int);
HAMON_STRICT_WEAK_ORDER_TEST(true,  const F&, const int, const int);

}	// namespace strict_weak_order_test

}	// namespace hamon_concepts_test

#undef HAMON_STRICT_WEAK_ORDER_TEST
