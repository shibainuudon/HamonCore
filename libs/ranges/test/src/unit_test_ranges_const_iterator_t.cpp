/**
 *	@file	unit_test_ranges_const_iterator_t.cpp
 *
 *	@brief	ranges::const_iterator_t のテスト
 */

#include <hamon/ranges/const_iterator_t.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_CONST_ITERATOR_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::const_iterator_t<C>, I>::value, "")

HAMON_RANGES_CONST_ITERATOR_T_TEST(char      [2],                  hamon::basic_const_iterator<char*>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(char const[2],                  char const*);
HAMON_RANGES_CONST_ITERATOR_T_TEST(char      (&)[2],               hamon::basic_const_iterator<char*>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(char const(&)[2],               char const*);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_contiguous_range<char>,    hamon::basic_const_iterator<contiguous_iterator_wrapper<char>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_random_access_range<char>, hamon::basic_const_iterator<random_access_iterator_wrapper<char>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_bidirectional_range<char>, hamon::basic_const_iterator<bidirectional_iterator_wrapper<char>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_forward_range<char>,       hamon::basic_const_iterator<forward_iterator_wrapper<char>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_input_range<char>,         hamon::basic_const_iterator<input_iterator_wrapper<char>>);
//HAMON_RANGES_CONST_ITERATOR_T_TEST(test_output_range<char>,        hamon::basic_const_iterator<output_iterator_wrapper<char>>);

HAMON_RANGES_CONST_ITERATOR_T_TEST(int      [2],                  hamon::basic_const_iterator<int*>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(int const[2],                  int const*);
HAMON_RANGES_CONST_ITERATOR_T_TEST(int      (&)[2],               hamon::basic_const_iterator<int*>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(int const(&)[2],               int const*);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_contiguous_range<int>,    hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_random_access_range<int>, hamon::basic_const_iterator<random_access_iterator_wrapper<int>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_bidirectional_range<int>, hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_forward_range<int>,       hamon::basic_const_iterator<forward_iterator_wrapper<int>>);
HAMON_RANGES_CONST_ITERATOR_T_TEST(test_input_range<int>,         hamon::basic_const_iterator<input_iterator_wrapper<int>>);
//HAMON_RANGES_CONST_ITERATOR_T_TEST(test_output_range<int>,        hamon::basic_const_iterator<output_iterator_wrapper<int>>);

#undef HAMON_RANGES_CONST_ITERATOR_T_TEST
