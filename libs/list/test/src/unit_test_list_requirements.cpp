/**
 *	@file	unit_test_list_requirements.cpp
 *
 *	@brief
 */

#include <hamon/list.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_list_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	hamon::detail::container_requirements<hamon::list<T>, T>();
}

GTEST_TEST(ListTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_list_test
