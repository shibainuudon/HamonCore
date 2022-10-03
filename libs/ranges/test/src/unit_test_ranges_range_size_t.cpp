/**
 *	@file	unit_test_ranges_range_size_t.cpp
 *
 *	@brief	ranges::range_size_t のテスト
 */

#include <hamon/ranges/range_size_t.hpp>
#include <type_traits>
#include <cstddef>
#include "ranges_test.hpp"

#define HAMON_RANGES_RANGE_SIZE_T_TEST(C, I)	\
	static_assert(std::is_same<hamon::ranges::range_size_t<C>, I>::value, "")

HAMON_RANGES_RANGE_SIZE_T_TEST(int      [2],                  std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(int const[2],                  std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(int      (&)[2],               std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(int const(&)[2],               std::size_t);

HAMON_RANGES_RANGE_SIZE_T_TEST(test_contiguous_range<int>,    std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_random_access_range<int>, std::size_t);
//HAMON_RANGES_RANGE_SIZE_T_TEST(test_bidirectional_range<int>, std::size_t);
//HAMON_RANGES_RANGE_SIZE_T_TEST(test_forward_range<int>,       std::size_t);
//HAMON_RANGES_RANGE_SIZE_T_TEST(test_input_range<int>,         std::size_t);
//HAMON_RANGES_RANGE_SIZE_T_TEST(test_output_range<int>,        std::size_t);

HAMON_RANGES_RANGE_SIZE_T_TEST(test_contiguous_sized_range<int>,    std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_random_access_sized_range<int>, std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_bidirectional_sized_range<int>, std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_forward_sized_range<int>,       std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_input_sized_range<int>,         std::size_t);
HAMON_RANGES_RANGE_SIZE_T_TEST(test_output_sized_range<int>,        std::size_t);

#undef HAMON_RANGES_RANGE_SIZE_T_TEST
