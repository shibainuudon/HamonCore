/**
 *	@file	unit_test_ranges_contiguous_range.cpp
 *
 *	@brief	ranges::contiguous_range のテスト
 */

#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/array.hpp>
#include <hamon/deque.hpp>
#include <hamon/forward_list.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>
#include <set>
#include <unordered_set>
#include <string>
#include "ranges_test.hpp"

#if defined(HAMON_HAS_CXX20_CONCEPTS)
#  define HAMON_RANGES_CONTIGUOUS_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::contiguous_range<__VA_ARGS__>, "");	\
	static_assert(B == hamon::ranges::contiguous_range_t<__VA_ARGS__>::value, "")
#else
#  define HAMON_RANGES_CONTIGUOUS_RANGE_TEST(B, ...)	\
	static_assert(B == hamon::ranges::contiguous_range<__VA_ARGS__>::value, "");	\
	static_assert(B == hamon::ranges::contiguous_range_t<__VA_ARGS__>::value, "")
#endif

HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      [2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int      []);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int const[]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      (&)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const(&)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int      (&&)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  int const(&&)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int      (*)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int const(*)[2]);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int      *);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, int const*);

#if 0
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  hamon::array<int, 2>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  hamon::vector<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, hamon::deque<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, hamon::list<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, hamon::forward_list<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, std::set<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, std::multiset<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, std::unordered_set<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, std::unordered_multiset<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  std::string);
#endif

HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_range<int>&&);

HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(true,  test_contiguous_sized_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_random_access_sized_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_bidirectional_sized_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_forward_sized_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_input_sized_range<int>&&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>&);
HAMON_RANGES_CONTIGUOUS_RANGE_TEST(false, test_output_sized_range<int>&&);

#undef HAMON_RANGES_CONTIGUOUS_RANGE_TEST
