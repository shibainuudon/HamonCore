﻿/**
 *	@file	unit_test_ranges_random_access_range.cpp
 *
 *	@brief	ranges::random_access_range のテスト
 */

#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/set.hpp>
#include <hamon/string.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/vector.hpp>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::random_access_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::random_access_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::random_access_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::random_access_range_t<__VA_ARGS__>::value, "")
#endif

HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int      [2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int      []);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int const[]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int      (&)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int      (&&)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int      *);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, int const*);

HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  hamon::array<int, 2>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  hamon::vector<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  hamon::deque<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::list<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::forward_list<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::set<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::multiset<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::unordered_set<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, hamon::unordered_multiset<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  hamon::string);

HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_range<int>&&);

HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(true,  test_random_access_sized_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_bidirectional_sized_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_forward_sized_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_input_sized_range<int>&&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_sized_range<int>);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_sized_range<int>&);
HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST(false, test_output_sized_range<int>&&);

#undef HAMON_RANGES_RANDOM_ACCESS_RANGE_TEST
