/**
 *	@file	unit_test_iterator_indirect_result_t.cpp
 *
 *	@brief	indirect_result_t のテスト
 */

#include <hamon/iterator/indirect_result_t.hpp>
#include <type_traits>
#include <vector>

namespace hamon_iterator_test
{

namespace indirect_result_t_test
{

static_assert(std::is_same<hamon::indirect_result_t<int(int), int*>, int>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<int(int), int const*>, int>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<int(int), std::vector<int>::iterator>, int>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<int(int), std::vector<int>::const_iterator>, int>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<float(int, int), int*, int*>, float>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<float(int, int), int const*, int const*>, float>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<float(int, int), int*, std::vector<int>::iterator>, float>::value, "");
static_assert(std::is_same<hamon::indirect_result_t<float(int, int), int*, std::vector<int>::const_iterator>, float>::value, "");

}	// namespace indirect_result_t_test

}	// namespace hamon_iterator_test
