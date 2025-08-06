/**
 *	@file	unit_test_hive.cpp
 *
 *	@brief	hive のテスト
 */

#include <hamon/hive.hpp>
#include <gtest/gtest.h>

GTEST_TEST(HiveTest, HiveTest)
{
	hamon::hive<int> i_hive;
	hamon::hive<int>::iterator it;
	hamon::hive<int *> p_hive;
	hamon::hive<int *>::iterator p_it;

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
