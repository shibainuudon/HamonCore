/**
 *	@file	unit_test_iterator_const_iterator.cpp
 *
 *	@brief	const_iterator のテスト
 */

#include <hamon/iterator/const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <vector>

static_assert(hamon::is_same<hamon::const_iterator<int*>, hamon::basic_const_iterator<int*>>::value, "");
static_assert(hamon::is_same<hamon::const_iterator<const int*>, const int*>::value, "");

static_assert(hamon::is_same<hamon::const_iterator<typename std::vector<int>::iterator>, hamon::basic_const_iterator<typename std::vector<int>::iterator>>::value, "");
static_assert(hamon::is_same<hamon::const_iterator<typename std::vector<int>::const_iterator>, typename std::vector<int>::const_iterator>::value, "");
