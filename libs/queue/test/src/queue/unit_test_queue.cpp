/**
 *	@file	unit_test_queue.cpp
 *
 *	@brief	queue のテスト
 */

#include <hamon/queue.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(QueueTest, QueueTest)
{
	hamon::queue<int> q;

	q.push(0); // back pushes 0
	q.push(1); // q = 0 1
	q.push(2); // q = 0 1 2
	q.push(3); // q = 0 1 2 3

	EXPECT_TRUE(q.front() == 0);
	EXPECT_TRUE(q.back() == 3);
	EXPECT_TRUE(q.size() == 4);

	q.pop(); // removes the front element, 0
	EXPECT_TRUE(q.size() == 3);

	// Print and remove all elements. Note that std::queue does not
	// support begin()/end(), so a range-for-loop cannot be used.
	std::stringstream ss;
	for (; !q.empty(); q.pop())
	{
		ss << q.front() << ' ';
	}
	EXPECT_EQ("1 2 3 ", ss.str());
	EXPECT_TRUE(q.size() == 0);
}
