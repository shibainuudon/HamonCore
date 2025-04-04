﻿/**
 *	@file	unit_test_iterator_const_sentinel.cpp
 *
 *	@brief	const_sentinel のテスト
 */

#include <hamon/iterator/const_sentinel.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>

static_assert(hamon::is_same<hamon::const_sentinel<int*>, hamon::basic_const_iterator<int*>>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<const int*>, const int*>::value, "");

static_assert(hamon::is_same<hamon::const_sentinel<typename hamon::vector<int>::iterator>, hamon::basic_const_iterator<typename hamon::vector<int>::iterator>>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<typename hamon::vector<int>::const_iterator>, typename hamon::vector<int>::const_iterator>::value, "");

static_assert(hamon::is_same<hamon::const_sentinel<hamon::default_sentinel_t>, hamon::default_sentinel_t>::value, "");
static_assert(hamon::is_same<hamon::const_sentinel<hamon::unreachable_sentinel_t>, hamon::unreachable_sentinel_t>::value, "");
