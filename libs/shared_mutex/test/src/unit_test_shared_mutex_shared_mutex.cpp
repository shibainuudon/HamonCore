/**
 *	@file	unit_test_shared_mutex_shared_mutex.cpp
 *
 *	@brief	shared_mutex のテスト
 */

#include <hamon/shared_mutex/shared_mutex.hpp>
#include <hamon/shared_mutex/shared_lock.hpp>
#include <gtest/gtest.h>
#include <mutex>
#include <thread>
#include <iostream>

namespace hamon_shared_mutex_test
{

namespace shared_mutex_test
{

std::mutex print_mtx;
void print_value(int x)
{
	std::lock_guard<std::mutex> lock(print_mtx);
	std::cout << x << std::endl;
}

class X
{
	hamon::shared_mutex mtx_;
public:
	int count_ = 0;

	// 書き込み側：カウンタを加算する
	void writer()
	{
		std::lock_guard<hamon::shared_mutex> lock(mtx_);
		++count_;
	}

	// 読み込み側：カウンタの値を読む
	void reader()
	{
		int local_count;
		{
			hamon::shared_lock<hamon::shared_mutex> lock(mtx_);
			local_count = count_;
		} // 共有ロックをここで手放す

		(void)local_count;
		//print_value(local_count);
	}
};

X obj;

void writer_thread()
{
	for (int i = 0; i < 3; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		obj.writer();
	}
}

void reader_thread()
{
	for (int i = 0; i < 10; ++i)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		obj.reader();
	}
}

GTEST_TEST(SharedMutexTest, SharedMutexTest)
{
	obj.count_ = 0;

	// 書き込みユーザー1人
	// 読み込みユーザー3人
	std::thread writer1(writer_thread);
	std::thread reader1(reader_thread);
	std::thread reader2(reader_thread);
	std::thread reader3(reader_thread);

	writer1.join();
	reader1.join();
	reader2.join();
	reader3.join();

	EXPECT_EQ(3, obj.count_);
}

}	// namespace shared_mutex_test

}	// namespace hamon_shared_mutex_test
