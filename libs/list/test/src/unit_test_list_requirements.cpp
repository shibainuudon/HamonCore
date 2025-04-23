/**
 *	@file	unit_test_list_requirements.cpp
 *
 *	@brief
 */

#include <hamon/list.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <hamon/container/detail/reversible_container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_list_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	// [list.overview]/2
	hamon::detail::container_requirements<hamon::list<T>, T>();
	hamon::detail::reversible_container_requirements<hamon::list<T>, T>();
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
