/**
 *	@file	unit_test_ranges_sentinel_t.cpp
 *
 *	@brief	ranges::sentinel_t のテスト
 */

#include <hamon/ranges/sentinel_t.hpp>
#include <type_traits>
#include "ranges_test.hpp"

#define HAMON_RANGES_SENTINEL_T_TEST(C, I)	\
	static_assert(std::is_same<hamon::ranges::sentinel_t<C>, I>::value, "")

HAMON_RANGES_SENTINEL_T_TEST(char      [2],                  char      *);
HAMON_RANGES_SENTINEL_T_TEST(char const[2],                  char const*);
HAMON_RANGES_SENTINEL_T_TEST(char      (&)[2],               char      *);
HAMON_RANGES_SENTINEL_T_TEST(char const(&)[2],               char const*);
HAMON_RANGES_SENTINEL_T_TEST(test_contiguous_range<char>,    test_contiguous_range<char>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_random_access_range<char>, test_random_access_range<char>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_bidirectional_range<char>, test_bidirectional_range<char>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_forward_range<char>,       test_forward_range<char>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_input_range<char>,         test_input_range<char>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_output_range<char>,        test_output_range<char>::sentinel);

HAMON_RANGES_SENTINEL_T_TEST(int      [2],                  int      *);
HAMON_RANGES_SENTINEL_T_TEST(int const[2],                  int const*);
HAMON_RANGES_SENTINEL_T_TEST(int      (&)[2],               int      *);
HAMON_RANGES_SENTINEL_T_TEST(int const(&)[2],               int const*);
HAMON_RANGES_SENTINEL_T_TEST(test_contiguous_range<int>,    test_contiguous_range<int>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_random_access_range<int>, test_random_access_range<int>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_bidirectional_range<int>, test_bidirectional_range<int>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_forward_range<int>,       test_forward_range<int>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_input_range<int>,         test_input_range<int>::sentinel);
HAMON_RANGES_SENTINEL_T_TEST(test_output_range<int>,        test_output_range<int>::sentinel);

#undef HAMON_RANGES_SENTINEL_T_TEST
