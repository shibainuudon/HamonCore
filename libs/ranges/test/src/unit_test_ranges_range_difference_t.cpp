/**
 *	@file	unit_test_ranges_range_difference_t.cpp
 *
 *	@brief	ranges::range_difference_t のテスト
 */

#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::range_difference_t<C>, I>::value, "")

HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(char      [2],                  hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(char const[2],                  hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(char      (&)[2],               hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(char const(&)[2],               hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_contiguous_range<char>,    hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_random_access_range<char>, hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_bidirectional_range<char>, hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_forward_range<char>,       hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_input_range<char>,         hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_output_range<char>,        hamon::ptrdiff_t);

HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(int      [2],                  hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(int const[2],                  hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(int      (&)[2],               hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(int const(&)[2],               hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_contiguous_range<int>,    hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_random_access_range<int>, hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_bidirectional_range<int>, hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_forward_range<int>,       hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_input_range<int>,         hamon::ptrdiff_t);
HAMON_RANGES_RANGE_DIFFERENCE_T_TEST(test_output_range<int>,        hamon::ptrdiff_t);

#undef HAMON_RANGES_RANGE_DIFFERENCE_T_TEST
