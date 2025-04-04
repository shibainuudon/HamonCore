﻿/**
 *	@file	unit_test_map_requirements.cpp
 *
 *	@brief
 */

#include <hamon/map/map.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_map_test
{

namespace requirements_test
{

template <typename Key, typename T>
void test()
{
#if defined(HAMON_USE_STD_MAP)
	hamon::detail::container_requirements<hamon::map<Key, T>, std::pair<const Key, T>>();
#else
	hamon::detail::container_requirements<hamon::map<Key, T>, hamon::pair<const Key, T>>();
#endif
}

GTEST_TEST(MapTest, RequirementsTest)
{
	test<int, int>();
	test<int, char>();
	test<int, float>();
	test<char, int>();
	test<char, char>();
	test<char, float>();
	test<float, int>();
	test<float, char>();
	test<float, float>();
}

}	// namespace requirements_test

}	// namespace hamon_map_test
