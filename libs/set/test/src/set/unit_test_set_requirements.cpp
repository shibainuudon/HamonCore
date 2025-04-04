/**
 *	@file	unit_test_set_requirements.cpp
 *
 *	@brief
 */

#include <hamon/set/set.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_set_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	hamon::detail::container_requirements<hamon::set<T>, T>();
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
