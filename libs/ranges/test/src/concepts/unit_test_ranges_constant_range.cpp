/**
 *	@file	unit_test_ranges_constant_range.cpp
 *
 *	@brief	ranges::constant_range のテスト
 */

#include <hamon/ranges/concepts/constant_range.hpp>
#include <hamon/vector.hpp>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_CONSTANT_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::constant_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::constant_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_CONSTANT_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::constant_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::constant_range_t<__VA_ARGS__>::value, "")
#endif

HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      [2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      []);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int const[]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      (&)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      (&&)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int      *);
HAMON_RANGES_CONSTANT_RANGE_TEST(false, int const*);

HAMON_RANGES_CONSTANT_RANGE_TEST(false, hamon::vector<int>);
HAMON_RANGES_CONSTANT_RANGE_TEST(true,  hamon::vector<int> const);

#undef HAMON_RANGES_CONSTANT_RANGE_TEST
