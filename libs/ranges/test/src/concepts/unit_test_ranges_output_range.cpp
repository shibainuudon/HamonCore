/**
 *	@file	unit_test_ranges_output_range.cpp
 *
 *	@brief	ranges::output_range のテスト
 */

#include <hamon/ranges/concepts/output_range.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <set>
#include <string>
#include <unordered_set>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_OUTPUT_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::output_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::output_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_OUTPUT_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::output_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::output_range_t<__VA_ARGS__>::value, "")
#endif

HAMON_RANGES_OUTPUT_RANGE_TEST(true,  int      [2],     int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const[2],     int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int      [],      int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const[],      int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  int      (&)[2],  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const(&)[2],  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  int      (&&)[2], int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const(&&)[2], int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int      (*)[2],  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const(*)[2],  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int      *,       int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, int const*,       int);

HAMON_RANGES_OUTPUT_RANGE_TEST(true,  hamon::array<int, 2>,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  hamon::vector<int>,           int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  hamon::deque<int>,            int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  hamon::list<int>,             int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  hamon::forward_list<int>,     int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, std::set<int>,                int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, std::multiset<int>,           int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, std::unordered_set<int>,      int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, std::unordered_multiset<int>, int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  std::string,                  char);

HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>,            int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>&,           int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_range<int>&&,          int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>&,        int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_range<int>&&,       int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>&,        int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_range<int>&&,       int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>,               int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>&,              int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_range<int>&&,             int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>,                 int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>&,                int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_range<int>&&,               int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>,                int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>&,               int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_range<int>&&,              int);

HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>,      int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>&,     int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_contiguous_sized_range<int>&&,    int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>,   int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>&,  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_random_access_sized_range<int>&&, int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>,   int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>&,  int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&, int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>&,        int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_forward_sized_range<int>&&,       int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>,           int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>&,          int);
HAMON_RANGES_OUTPUT_RANGE_TEST(false, test_input_sized_range<int>&&,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>,          int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>&,         int);
HAMON_RANGES_OUTPUT_RANGE_TEST(true,  test_output_sized_range<int>&&,        int);

#undef HAMON_RANGES_OUTPUT_RANGE_TEST
