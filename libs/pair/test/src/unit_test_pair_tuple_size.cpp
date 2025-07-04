/**
 *	@file	unit_test_pair_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 */

#include <hamon/pair.hpp>
#include <hamon/tuple.hpp>

namespace hamon_pair_test
{

namespace tuple_size_test
{

static_assert(hamon::tuple_size<hamon::pair<int, float>>::value == 2, "");
static_assert(hamon::tuple_size<hamon::pair<int, float> const>::value == 2, "");
static_assert(hamon::tuple_size<hamon::pair<int, float> volatile>::value == 2, "");
static_assert(hamon::tuple_size<hamon::pair<int, float> const volatile>::value == 2, "");

}	// namespace tuple_size_test

}	// namespace hamon_pair_test
