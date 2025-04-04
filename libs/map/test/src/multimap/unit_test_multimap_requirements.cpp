﻿/**
 *	@file	unit_test_multimap_requirements.cpp
 *
 *	@brief
 */

#include <hamon/map/multimap.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_multimap_test
{

namespace requirements_test
{

template <typename Key, typename T>
void test()
{
#if defined(HAMON_USE_STD_MULTIMAP)
	hamon::detail::container_requirements<hamon::multimap<Key, T>, std::pair<const Key, T>>();
#else
	hamon::detail::container_requirements<hamon::multimap<Key, T>, hamon::pair<const Key, T>>();
#endif
}

GTEST_TEST(MultimapTest, RequirementsTest)
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

}	// namespace hamon_multimap_test
