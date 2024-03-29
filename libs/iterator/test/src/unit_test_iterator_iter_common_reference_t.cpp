﻿/**
 *	@file	unit_test_iterator_iter_common_reference_t.cpp
 *
 *	@brief	iter_common_reference_t のテスト
 */

#include <hamon/iterator/iter_common_reference_t.hpp>
#include <hamon/iterator/projected.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/list.hpp>
#include <hamon/vector.hpp>

namespace hamon_iterator_test
{

namespace iter_common_reference_t_test
{

static_assert(hamon::is_same<hamon::iter_common_reference_t<int*>, int&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<char const*>, char const&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<hamon::vector<float>::iterator>, float&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<hamon::vector<float>::const_iterator>, float const&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<hamon::list<double>::iterator>, double&>::value, "");
static_assert(hamon::is_same<hamon::iter_common_reference_t<hamon::list<double>::const_iterator>, double const&>::value, "");

// P2609R3

struct MoveOnly
{
	MoveOnly(MoveOnly&&) = default;
	MoveOnly(MoveOnly const&) = delete;
};
struct Proj
{
	MoveOnly operator()(int) const;
};
static_assert(hamon::is_same<hamon::iter_common_reference_t<hamon::projected<int*, Proj>>, MoveOnly>::value, "");

}	// namespace iter_common_reference_t_test

}	// namespace hamon_iterator_test
