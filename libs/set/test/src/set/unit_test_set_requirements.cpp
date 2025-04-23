/**
 *	@file	unit_test_set_requirements.cpp
 *
 *	@brief
 */

#include <hamon/set/set.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <hamon/container/detail/reversible_container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_set_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	// [set.overview]/2
	hamon::detail::container_requirements<hamon::set<T>, T>();
	hamon::detail::reversible_container_requirements<hamon::set<T>, T>();
}

GTEST_TEST(SetTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_set_test
