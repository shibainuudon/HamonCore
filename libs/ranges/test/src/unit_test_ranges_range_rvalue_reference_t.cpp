/**
 *	@file	unit_test_ranges_range_rvalue_reference_t.cpp
 *
 *	@brief	ranges::range_rvalue_reference_t のテスト
 */

#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::range_rvalue_reference_t<C>, I>::value, "")

HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char      [2],                  char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char const[2],                  char const&&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char      (&)[2],               char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(char const(&)[2],               char const&&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_contiguous_range<char>,    char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_random_access_range<char>, char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_bidirectional_range<char>, char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_forward_range<char>,       char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_input_range<char>,         char      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_output_range<char>,        char      &&);

HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int      [2],                  int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int const[2],                  int const&&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int      (&)[2],               int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(int const(&)[2],               int const&&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_contiguous_range<int>,    int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_random_access_range<int>, int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_bidirectional_range<int>, int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_forward_range<int>,       int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_input_range<int>,         int      &&);
HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST(test_output_range<int>,        int      &&);

#undef HAMON_RANGES_RANGE_RVALUE_REFERENCE_T_TEST
