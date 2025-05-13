/**
 *	@file	unit_test_priority_queue.cpp
 *
 *	@brief	priority_queue のテスト
 */

#include <hamon/queue.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_priority_queue_test
{

namespace priority_queue_test
{

template<typename T>
void pop_println(std::stringstream& ss, T& pq)
{
	for (; !pq.empty(); pq.pop())
	{
		ss << pq.top() << ' ';
	}
}

GTEST_TEST(PriorityQueueTest, PriorityQueueTest)
{
	const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};

	hamon::priority_queue<int> max_priority_queue;

	// Fill the priority queue.
	for (int n : data)
	{
		max_priority_queue.push(n);
	}

	{
		std::stringstream ss;
		pop_println(ss, max_priority_queue);
		EXPECT_EQ("9 8 7 6 5 4 3 2 1 0 ", ss.str());
	}

	// std::greater<int> makes the max priority queue act as a min priority queue.
	{
		hamon::priority_queue<int, std::vector<int>, std::greater<int>>
			min_priority_queue1(data.begin(), data.end());

		std::stringstream ss;
		pop_println(ss, min_priority_queue1);
		EXPECT_EQ("0 1 2 3 4 5 6 7 8 9 ", ss.str());
	}

	// Second way to define a min priority queue.
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::priority_queue min_priority_queue2(data.begin(), data.end(), std::greater<int>());

		std::stringstream ss;
		pop_println(ss, min_priority_queue2);
		EXPECT_EQ("0 1 2 3 4 5 6 7 8 9 ", ss.str());
	}
#endif

	// Using a custom function object to compare elements.
	{
		struct CustomLess
		{
			bool operator()(const int l, const int r) const { return l > r; }
		};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
		hamon::priority_queue custom_priority_queue(data.begin(), data.end(), CustomLess{});
#else
		hamon::priority_queue<int, std::vector<int>, CustomLess>
			custom_priority_queue(data.begin(), data.end(), CustomLess{});
#endif

		std::stringstream ss;
		pop_println(ss, custom_priority_queue);
		EXPECT_EQ("0 1 2 3 4 5 6 7 8 9 ", ss.str());
	}

	// Using lambda to compare elements.
	{
		auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
		hamon::priority_queue<int, std::vector<int>, decltype(cmp)> lambda_priority_queue(cmp);

		for (int n : data)
		{
			lambda_priority_queue.push(n);
		}

		std::stringstream ss;
		pop_println(ss, lambda_priority_queue);
		EXPECT_EQ("8 9 6 7 4 5 2 3 0 1 ", ss.str());
	}
}

}	// namespace priority_queue_test

}	// namespace hamon_priority_queue_test
