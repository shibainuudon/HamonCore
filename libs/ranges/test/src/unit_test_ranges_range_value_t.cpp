/**
 *	@file	unit_test_ranges_range_value_t.cpp
 *
 *	@brief	ranges::range_value_t のテスト
 */

#include <hamon/ranges/range_value_t.hpp>
#include <type_traits>
#include "ranges_test.hpp"

#define HAMON_RANGES_RANGE_VALUE_T_TEST(C, I)	\
	static_assert(std::is_same<hamon::ranges::range_value_t<C>, I>::value, "")

HAMON_RANGES_RANGE_VALUE_T_TEST(char      [2],                  char);
HAMON_RANGES_RANGE_VALUE_T_TEST(char const[2],                  char);
HAMON_RANGES_RANGE_VALUE_T_TEST(char      (&)[2],               char);
HAMON_RANGES_RANGE_VALUE_T_TEST(char const(&)[2],               char);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_contiguous_range<char>,    char);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_random_access_range<char>, char);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_bidirectional_range<char>, char);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_forward_range<char>,       char);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_input_range<char>,         char);
//HAMON_RANGES_RANGE_VALUE_T_TEST(test_output_range<char>,        char);

HAMON_RANGES_RANGE_VALUE_T_TEST(int      [2],                  int);
HAMON_RANGES_RANGE_VALUE_T_TEST(int const[2],                  int);
HAMON_RANGES_RANGE_VALUE_T_TEST(int      (&)[2],               int);
HAMON_RANGES_RANGE_VALUE_T_TEST(int const(&)[2],               int);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_contiguous_range<int>,    int);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_random_access_range<int>, int);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_bidirectional_range<int>, int);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_forward_range<int>,       int);
HAMON_RANGES_RANGE_VALUE_T_TEST(test_input_range<int>,         int);
//HAMON_RANGES_RANGE_VALUE_T_TEST(test_output_range<int>,        int);

#undef HAMON_RANGES_RANGE_VALUE_T_TEST
