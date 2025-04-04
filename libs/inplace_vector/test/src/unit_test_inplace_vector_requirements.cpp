/**
 *	@file	unit_test_inplace_vector_requirements.cpp
 *
 *	@brief
 */

#include <hamon/inplace_vector.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_inplace_vector_test
{

namespace requirements_test
{

template <typename T, hamon::size_t N>
void test_impl()
{
	hamon::detail::container_requirements<hamon::inplace_vector<T, N>, T>();
}

template <typename T>
void test()
{
	test_impl<T, 0>();
	test_impl<T, 1>();
	test_impl<T, 2>();
	test_impl<T, 13>();
	test_impl<T, 255>();
}

GTEST_TEST(InplaceVectorTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_inplace_vector_test
