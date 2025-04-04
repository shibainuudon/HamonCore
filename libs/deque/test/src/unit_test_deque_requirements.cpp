/**
 *	@file	unit_test_deque_requirements.cpp
 *
 *	@brief
 */

#include <hamon/deque.hpp>
#include <hamon/container/detail/container_requirements.hpp>
#include <gtest/gtest.h>

namespace hamon_deque_test
{

namespace requirements_test
{

template <typename T>
void test()
{
	hamon::detail::container_requirements<hamon::deque<T>, T>();
}

GTEST_TEST(DequeTest, RequirementsTest)
{
	test<int>();
	test<unsigned int>();
	test<char>();
	test<float>();
	test<double>();
}

}	// namespace requirements_test

}	// namespace hamon_deque_test
