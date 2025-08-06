/**
 *	@file	unit_test_hive_pmr.cpp
 *
 *	@brief	pmr::hive のテスト
 */

#include <hamon/hive.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>

namespace hamon_hive_test
{

namespace pmr_test
{

GTEST_TEST(HiveTest, PmrTest)
{
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::hive<int> i_hive(&mr);
	hamon::pmr::hive<int>::iterator it;
	hamon::pmr::hive<int *> p_hive(&mr);
	hamon::pmr::hive<int *>::iterator p_it;

	// Insert 100 ints to i_hive and pointers to those ints to p_hive:
	for (int i = 0; i != 100; ++i)
	{
		it = i_hive.insert(i);
		p_hive.insert(&(*it));
	}

	// Erase half of the ints:
	for (it = i_hive.begin(); it != i_hive.end(); ++it)
	{
		it = i_hive.erase(it);
	}

	// Erase half of the int pointers:
	for (p_it = p_hive.begin(); p_it != p_hive.end(); ++p_it)
	{
		p_it = p_hive.erase(p_it);
	}

	// Total the remaining ints via the pointer hive (pointers will still be valid even after insertions and erasures):
	int total = 0;

	for (p_it = p_hive.begin(); p_it != p_hive.end(); ++p_it)
	{
		total += *(*p_it);
	}

	EXPECT_EQ(2500, total);
}

}	// namespace pmr_test

}	// namespace hamon_hive_test
