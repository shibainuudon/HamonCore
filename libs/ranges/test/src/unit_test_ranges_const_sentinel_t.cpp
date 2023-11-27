/**
 *	@file	unit_test_ranges_const_sentinel_t.cpp
 *
 *	@brief	ranges::const_sentinel_t のテスト
 */

#include <hamon/ranges/const_sentinel_t.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_CONST_SENTINEL_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::const_sentinel_t<C>, I>::value, "")

HAMON_RANGES_CONST_SENTINEL_T_TEST(char      [2],                  hamon::basic_const_iterator<char*>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(char const[2],                  char const*);
HAMON_RANGES_CONST_SENTINEL_T_TEST(char      (&)[2],               hamon::basic_const_iterator<char*>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(char const(&)[2],               char const*);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_contiguous_range<char>,    test_sentinel<contiguous_iterator_wrapper<char>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_random_access_range<char>, test_sentinel<random_access_iterator_wrapper<char>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_bidirectional_range<char>, test_sentinel<bidirectional_iterator_wrapper<char>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_forward_range<char>,       test_sentinel<forward_iterator_wrapper<char>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_input_range<char>,         test_sentinel<input_iterator_wrapper<char>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_output_range<char>,        test_sentinel<output_iterator_wrapper<char>>);

HAMON_RANGES_CONST_SENTINEL_T_TEST(int      [2],                  hamon::basic_const_iterator<int*>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(int const[2],                  int const*);
HAMON_RANGES_CONST_SENTINEL_T_TEST(int      (&)[2],               hamon::basic_const_iterator<int*>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(int const(&)[2],               int const*);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_contiguous_range<int>,    test_sentinel<contiguous_iterator_wrapper<int>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_random_access_range<int>, test_sentinel<random_access_iterator_wrapper<int>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_bidirectional_range<int>, test_sentinel<bidirectional_iterator_wrapper<int>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_forward_range<int>,       test_sentinel<forward_iterator_wrapper<int>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_input_range<int>,         test_sentinel<input_iterator_wrapper<int>>);
HAMON_RANGES_CONST_SENTINEL_T_TEST(test_output_range<int>,        test_sentinel<output_iterator_wrapper<int>>);

#undef HAMON_RANGES_CONST_SENTINEL_T_TEST
