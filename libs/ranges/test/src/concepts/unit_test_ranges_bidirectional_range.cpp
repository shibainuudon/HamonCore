/**
 *	@file	unit_test_ranges_bidirectional_range.cpp
 *
 *	@brief	ranges::bidirectional_range のテスト
 */

#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <string>
#include <unordered_set>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::bidirectional_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::bidirectional_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::bidirectional_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::bidirectional_range_t<__VA_ARGS__>::value, "")
#endif

HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int      [2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int      []);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int const[]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int      (&)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int      (&&)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int      *);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, int const*);

HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::array<int, 2>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::vector<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::deque<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::list<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, std::forward_list<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::set<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::multiset<int>);
//HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::unordered_set<int>);
//HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::unordered_multiset<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  std::string);

HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_range<int>&&);

HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_random_access_sized_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(true,  test_bidirectional_sized_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_forward_sized_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_input_sized_range<int>&&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_sized_range<int>);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_sized_range<int>&);
HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST(false, test_output_sized_range<int>&&);

#undef HAMON_RANGES_BIDIRECTIONAL_RANGE_TEST
