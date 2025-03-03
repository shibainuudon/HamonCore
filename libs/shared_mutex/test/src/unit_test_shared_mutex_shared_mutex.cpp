/**
 *	@file	unit_test_shared_mutex_shared_mutex.cpp
 *
 *	@brief	shared_mutex のテスト
 */

#include <hamon/shared_mutex/shared_mutex.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <chrono>

namespace hamon_shared_mutex_test
{

namespace shared_mutex_test
{

void test_one_writer()
{
	// One simultaneous writer.
	std::atomic<int> atom(-1);
	hamon::shared_mutex mut;
	hamon::vector<std::thread> threads;

	for (int i = 0; i < 4; ++i)
	{
		threads.emplace_back([&atom, &mut]
		{
			while (atom == -1) {}
			mut.lock();
			const int val = ++atom;
			std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Not a timing assumption.
			EXPECT_TRUE(atom == val);
			mut.unlock();
		});
	}

	EXPECT_TRUE(atom.exchange(0) == -1);

	for (auto& t : threads)
	{
		t.join();
	}

	EXPECT_TRUE(atom == 4);
}

void test_multiple_readers()
{
	// Many simultaneous readers.
	std::atomic<int> atom(-1);
	hamon::shared_mutex mut;
	hamon::vector<std::thread> threads;

	for (int i = 0; i < 4; ++i)
	{
		threads.emplace_back([&atom, &mut]
		{
			while (atom == -1) {}
			mut.lock_shared();
			++atom;
			while (atom < 4) {}
			mut.unlock_shared();
		});
	}

	EXPECT_TRUE(atom.exchange(0) == -1);

	for (auto& t : threads)
	{
		t.join();
	}

	EXPECT_TRUE(atom == 4);
}

void test_writer_blocking_readers()
{
	// One writer blocking many readers.
	std::atomic<int> atom(-4);
	hamon::shared_mutex mut;
	hamon::vector<std::thread> threads;

	threads.emplace_back([&atom, &mut]
	{
		while (atom < 0) {}
		mut.lock();
		EXPECT_TRUE(atom.exchange(1000) == 0);
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Not a timing assumption.
		EXPECT_TRUE(atom.exchange(1729) == 1000);
		mut.unlock();
	});

	for (int i = 0; i < 4; ++i)
	{
		threads.emplace_back([&atom, &mut]
		{
			++atom;
			while (atom < 1000) {}
			mut.lock_shared();
			EXPECT_TRUE(atom == 1729);
			mut.unlock_shared();
		});
	}

	for (auto& t : threads)
	{
		t.join();
	}

	EXPECT_TRUE(atom == 1729);
}

void test_readers_blocking_writer()
{
	// Many readers blocking one writer.
	std::atomic<int> atom(-5);
	hamon::shared_mutex mut;
	hamon::vector<std::thread> threads;

	for (int i = 0; i < 4; ++i)
	{
		threads.emplace_back([&atom, &mut]
		{
			mut.lock_shared();
			++atom;
			while (atom < 0){}
			std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Not a timing assumption.
			atom += 10;
			mut.unlock_shared();
		});
	}

	threads.emplace_back([&atom, &mut]
	{
		++atom;
		while (atom < 0) {}
		mut.lock();
		EXPECT_TRUE(atom == 40);
		mut.unlock();
	});

	for (auto& t : threads)
	{
		t.join();
	}

	EXPECT_TRUE(atom == 40);
}

void test_try_lock_and_try_lock_shared()
{
	// Test try_lock() and try_lock_shared().
	hamon::shared_mutex mut;

	{
		EXPECT_TRUE(mut.try_lock());

		std::thread t([&mut]
		{
			EXPECT_FALSE(mut.try_lock());
			EXPECT_FALSE(mut.try_lock_shared());
		});

		t.join();
		mut.unlock();
	}

	{
		EXPECT_TRUE(mut.try_lock_shared());

		std::thread t([&mut]
		{
			EXPECT_FALSE(mut.try_lock());
			EXPECT_TRUE (mut.try_lock_shared());
			mut.unlock_shared();
		});

		t.join();
		mut.unlock_shared();
	}
}

GTEST_TEST(SharedMutexTest, SharedMutexTest)
{
	test_one_writer();
	test_multiple_readers();
	test_writer_blocking_readers();
	test_readers_blocking_writer();
	test_try_lock_and_try_lock_shared();
}

}	// namespace shared_mutex_test

}	// namespace hamon_shared_mutex_test
