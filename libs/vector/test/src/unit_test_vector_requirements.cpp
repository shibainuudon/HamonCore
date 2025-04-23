/**
 *	@file	unit_test_vector_requirements.cpp
 *
 *	@brief
 */

#include <hamon/vector.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <hamon/container/detail/reversible_container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_vector_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	// [vector.overview]/2
	hamon::detail::container_requirements<hamon::vector<T>, T>();
	hamon::detail::reversible_container_requirements<hamon::vector<T>, T>();
}

GTEST_TEST(VectorTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_vector_test
