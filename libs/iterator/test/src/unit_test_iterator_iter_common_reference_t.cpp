﻿/**
 *	@file	unit_test_iterator_iter_common_reference_t.cpp
 *
 *	@brief	iter_common_reference_t のテスト
 */

#include <hamon/iterator/iter_common_reference_t.hpp>
#include <type_traits>
#include <vector>
#include <list>

namespace hamon_iterator_test
{

namespace iter_common_reference_t_test
{

static_assert(std::is_same<hamon::iter_common_reference_t<int*>, int&>::value, "");
static_assert(std::is_same<hamon::iter_common_reference_t<char const*>, char const&>::value, "");
static_assert(std::is_same<hamon::iter_common_reference_t<std::vector<float>::iterator>, float&>::value, "");
static_assert(std::is_same<hamon::iter_common_reference_t<std::vector<float>::const_iterator>, float const&>::value, "");
static_assert(std::is_same<hamon::iter_common_reference_t<std::list<double>::iterator>, double&>::value, "");
static_assert(std::is_same<hamon::iter_common_reference_t<std::list<double>::const_iterator>, double const&>::value, "");

}	// namespace iter_common_reference_t_test

}	// namespace hamon_iterator_test