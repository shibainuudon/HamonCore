/**
 *	@file	unit_test_multiset_requirements.cpp
 *
 *	@brief
 */

#include <hamon/set/multiset.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_multiset_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	hamon::detail::container_requirements<hamon::multiset<T>, T>();
}

GTEST_TEST(MultisetTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_multiset_test
