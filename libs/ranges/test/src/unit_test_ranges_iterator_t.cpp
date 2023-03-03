/**
 *	@file	unit_test_ranges_iterator_t.cpp
 *
 *	@brief	ranges::iterator_t のテスト
 */

#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_ITERATOR_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::iterator_t<C>, I>::value, "")

HAMON_RANGES_ITERATOR_T_TEST(char      [2],                  char      *);
HAMON_RANGES_ITERATOR_T_TEST(char const[2],                  char const*);
HAMON_RANGES_ITERATOR_T_TEST(char      (&)[2],               char      *);
HAMON_RANGES_ITERATOR_T_TEST(char const(&)[2],               char const*);
HAMON_RANGES_ITERATOR_T_TEST(test_contiguous_range<char>,    contiguous_iterator_wrapper<char>);
HAMON_RANGES_ITERATOR_T_TEST(test_random_access_range<char>, random_access_iterator_wrapper<char>);
HAMON_RANGES_ITERATOR_T_TEST(test_bidirectional_range<char>, bidirectional_iterator_wrapper<char>);
HAMON_RANGES_ITERATOR_T_TEST(test_forward_range<char>,       forward_iterator_wrapper<char>);
HAMON_RANGES_ITERATOR_T_TEST(test_input_range<char>,         input_iterator_wrapper<char>);
HAMON_RANGES_ITERATOR_T_TEST(test_output_range<char>,        output_iterator_wrapper<char>);

HAMON_RANGES_ITERATOR_T_TEST(int      [2],                  int      *);
HAMON_RANGES_ITERATOR_T_TEST(int const[2],                  int const*);
HAMON_RANGES_ITERATOR_T_TEST(int      (&)[2],               int      *);
HAMON_RANGES_ITERATOR_T_TEST(int const(&)[2],               int const*);
HAMON_RANGES_ITERATOR_T_TEST(test_contiguous_range<int>,    contiguous_iterator_wrapper<int>);
HAMON_RANGES_ITERATOR_T_TEST(test_random_access_range<int>, random_access_iterator_wrapper<int>);
HAMON_RANGES_ITERATOR_T_TEST(test_bidirectional_range<int>, bidirectional_iterator_wrapper<int>);
HAMON_RANGES_ITERATOR_T_TEST(test_forward_range<int>,       forward_iterator_wrapper<int>);
HAMON_RANGES_ITERATOR_T_TEST(test_input_range<int>,         input_iterator_wrapper<int>);
HAMON_RANGES_ITERATOR_T_TEST(test_output_range<int>,        output_iterator_wrapper<int>);

#undef HAMON_RANGES_ITERATOR_T_TEST
