/**
 *	@file	unit_test_forward_list_requirements.cpp
 *
 *	@brief
 */

#include <hamon/forward_list.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_forward_list_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	hamon::detail::container_requirements<hamon::forward_list<T>, T, false>();
}

GTEST_TEST(ForwardListTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_forward_list_test
