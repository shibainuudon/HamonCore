/**
 *	@file	unit_test_ranges_borrowed_iterator_t.cpp
 *
 *	@brief	ranges::borrowed_iterator_t のテスト
 */

#include <hamon/ranges/borrowed_iterator_t.hpp>
#include <hamon/ranges/dangling.hpp>
//#include <hamon/ranges/views/subrange.hpp>
//#include <hamon/span.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <type_traits>
#include "ranges_test.hpp"

#define HAMON_RANGES_BORROWED_ITERATOR_T_TEST(C, I)	\
	static_assert(std::is_same<hamon::ranges::borrowed_iterator_t<C>, I>::value, "")

HAMON_RANGES_BORROWED_ITERATOR_T_TEST(char      [2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(char const[2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(char      (&)[2],                char      *);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(char const(&)[2],                char const*);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<char>,     hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<char>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<char>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<char>,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<char>,          hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<char>,         hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<char>&,    contiguous_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<char>&, random_access_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<char>&, bidirectional_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<char>&,       forward_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<char>&,         input_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<char>&,        output_iterator_wrapper<char>);
#if 0 // TODO
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<char*>,  char*);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<contiguous_iterator_wrapper<char>>,    contiguous_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<random_access_iterator_wrapper<char>>, random_access_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<bidirectional_iterator_wrapper<char>>, bidirectional_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<forward_iterator_wrapper<char>>,       forward_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<input_iterator_wrapper<char>>,         input_iterator_wrapper<char>);
//HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<output_iterator_wrapper<char>>,        output_iterator_wrapper<char>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::span<char>,               hamon::span<char>::iterator);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::span<char HAMON_PP_COMMA() 10>, hamon::span<char HAMON_PP_COMMA() 10>::iterator);
#endif

HAMON_RANGES_BORROWED_ITERATOR_T_TEST(int      [2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(int const[2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(int      (&)[2],                int      *);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(int const(&)[2],                int const*);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<int>,     hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<int>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<int>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<int>,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<int>,          hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<int>,         hamon::ranges::dangling);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_contiguous_range<int>&,    contiguous_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_random_access_range<int>&, random_access_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_bidirectional_range<int>&, bidirectional_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_forward_range<int>&,       forward_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_input_range<int>&,         input_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(test_output_range<int>&,        output_iterator_wrapper<int>);
#if 0 // TODO
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<int*>,  int*);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<contiguous_iterator_wrapper<int>>,    contiguous_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<random_access_iterator_wrapper<int>>, random_access_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<bidirectional_iterator_wrapper<int>>, bidirectional_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<forward_iterator_wrapper<int>>,       forward_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<input_iterator_wrapper<int>>,         input_iterator_wrapper<int>);
//HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::ranges::subrange<output_iterator_wrapper<int>>,        output_iterator_wrapper<int>);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::span<int>,               hamon::span<int>::iterator);
HAMON_RANGES_BORROWED_ITERATOR_T_TEST(hamon::span<int HAMON_PP_COMMA() 10>, hamon::span<int HAMON_PP_COMMA() 10>::iterator);
#endif

#undef HAMON_RANGES_BORROWED_ITERATOR_T_TEST
