/**
 *	@file	unit_test_iterator_const_sentinel.cpp
 *
 *	@brief	const_sentinel のテスト
 */

#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/unreachable_sentinel.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <vector>

static_assert(hamon::is_same<hamon::const_sentinel<int*>, hamon::basic_const_iterator<int*>>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<const int*>, const int*>::value, "");

static_assert(hamon::is_same<hamon::const_sentinel<typename std::vector<int>::iterator>, hamon::basic_const_iterator<typename std::vector<int>::iterator>>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<typename std::vector<int>::const_iterator>, typename std::vector<int>::const_iterator>::value, "");

static_assert(hamon::is_same<hamon::const_sentinel<hamon::default_sentinel_t>, hamon::default_sentinel_t>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<hamon::unreachable_sentinel_t>, hamon::unreachable_sentinel_t>::value, "");
