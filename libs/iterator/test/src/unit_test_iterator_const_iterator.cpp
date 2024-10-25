/**
 *	@file	unit_test_iterator_const_iterator.cpp
 *
 *	@brief	const_iterator のテスト
 */

#include <hamon/iterator/const_iterator.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>

static_assert(hamon::is_same<hamon::const_iterator<int*>, hamon::basic_const_iterator<int*>>::value, "");
static_assert(hamon::is_same<hamon::const_iterator<const int*>, const int*>::value, "");

static_assert(hamon::is_same<hamon::const_iterator<typename hamon::vector<int>::iterator>, hamon::basic_const_iterator<typename hamon::vector<int>::iterator>>::value, "");
static_assert(hamon::is_same<hamon::const_iterator<typename hamon::vector<int>::const_iterator>, typename hamon::vector<int>::const_iterator>::value, "");
