/**
 *	@file	unit_test_concepts_totally_ordered_with.cpp
 *
 *	@brief	totally_ordered_with のテスト
 */

#include <hamon/concepts/totally_ordered_with.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_TOTALLY_ORDERED_WITH_TEST(B, ...)	\
	static_assert(B == hamon::totally_ordered_with<__VA_ARGS__>, "");	\
	static_assert(B == hamon::totally_ordered_with_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_TOTALLY_ORDERED_WITH_TEST(B, ...) \
	static_assert(B == hamon::totally_ordered_with<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::totally_ordered_with_t<__VA_ARGS__>::value, "")
#endif

namespace hamon_concepts_test
{

namespace totally_ordered_with_test
{

HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, int);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, char);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, float);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, void);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int*);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, int&);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, int&&);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int[]);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int[2]);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int());
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int(*)());
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int, int(&)());

HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int, int const);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int const, int const);

HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int*, int*);
HAMON_TOTALLY_ORDERED_WITH_TEST(false, int*, float*);
HAMON_TOTALLY_ORDERED_WITH_TEST(true,  int*, void*);

}	// namespace totally_ordered_with_test

}	// namespace hamon_concepts_test

#undef HAMON_TOTALLY_ORDERED_WITH_TEST
