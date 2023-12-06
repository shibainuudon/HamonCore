/**
 *	@file	unit_test_ranges_borrowed_subrange_t.cpp
 *
 *	@brief	ranges::borrowed_subrange_t のテスト
 */

#include <hamon/ranges/borrowed_subrange_t.hpp>
#include <hamon/ranges/utility/dangling.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/span.hpp>
#include <hamon/preprocessor/punctuation/comma.hpp>
#include <hamon/type_traits/is_same.hpp>
#include "ranges_test.hpp"

#define HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(C, I)	\
	static_assert(hamon::is_same<hamon::ranges::borrowed_subrange_t<C>, I>::value, "")

HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(char      [2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(char const[2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(char      (&)[2],                hamon::ranges::subrange<char      *>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(char const(&)[2],                hamon::ranges::subrange<char const*>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<char>,     hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<char>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<char>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<char>,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<char>,          hamon::ranges::dangling);
//HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<char>,         hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<char>&,    hamon::ranges::subrange<contiguous_iterator_wrapper<char>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<char>&, hamon::ranges::subrange<random_access_iterator_wrapper<char>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<char>&, hamon::ranges::subrange<bidirectional_iterator_wrapper<char>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<char>&,       hamon::ranges::subrange<forward_iterator_wrapper<char>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<char>&,         hamon::ranges::subrange<input_iterator_wrapper<char>>);
//HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<char>&,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(hamon::span<char>,               hamon::ranges::subrange<hamon::span<char>::iterator>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(hamon::span<char HAMON_PP_COMMA() 10>, hamon::ranges::subrange<hamon::span<char HAMON_PP_COMMA() 10>::iterator>);

HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(int      [2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(int const[2],                   hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(int      (&)[2],                hamon::ranges::subrange<int      *>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(int const(&)[2],                hamon::ranges::subrange<int const*>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<int>,     hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<int>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<int>,  hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<int>,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<int>,          hamon::ranges::dangling);
//HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<int>,         hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_contiguous_range<int>&,    hamon::ranges::subrange<contiguous_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_random_access_range<int>&, hamon::ranges::subrange<random_access_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_bidirectional_range<int>&, hamon::ranges::subrange<bidirectional_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_forward_range<int>&,       hamon::ranges::subrange<forward_iterator_wrapper<int>>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_input_range<int>&,         hamon::ranges::subrange<input_iterator_wrapper<int>>);
//HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(test_output_range<int>&,        hamon::ranges::dangling);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(hamon::span<int>,               hamon::ranges::subrange<hamon::span<int>::iterator>);
HAMON_RANGES_BORROWED_SUBRANGE_T_TEST(hamon::span<int HAMON_PP_COMMA() 10>, hamon::ranges::subrange<hamon::span<int HAMON_PP_COMMA() 10>::iterator>);

#undef HAMON_RANGES_BORROWED_SUBRANGE_T_TEST
