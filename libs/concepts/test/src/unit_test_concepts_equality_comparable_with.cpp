/**
 *	@file	unit_test_concepts_equality_comparable_with.cpp
 *
 *	@brief	equality_comparable_with のテスト
 */

#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_EQUALITY_COMPARABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::equality_comparable_with<T1, T2>, "");	\
	static_assert(B == hamon::equality_comparable_with_t<T1, T2>::value, "")
#else
#  define HAMON_EQUALITY_COMPARABLE_WITH_TEST(B, T1, T2)	\
	static_assert(B == hamon::equality_comparable_with<T1, T2>::value, "");	\
	static_assert(B == hamon::equality_comparable_with_t<T1, T2>::value, "")
#endif

namespace hamon_concepts_test
{

namespace equality_comparable_with_test
{

HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, char);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, float);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, void);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int*);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int&);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int&&);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int[]);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int[2]);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int());
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int(*)());
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int, int(&)());

HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int, int const);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int const, int const);

HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int*, int*);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(false, int*, float*);
HAMON_EQUALITY_COMPARABLE_WITH_TEST(true,  int*, void*);

}	// namespace equality_comparable_with_test

}	// namespace hamon_concepts_test

#undef HAMON_EQUALITY_COMPARABLE_WITH_TEST
