/**
 *	@file	unit_test_shared_mutex_shared_timed_mutex.cpp
 *
 *	@brief	shared_timed_mutex のテスト
 */

#include <hamon/shared_mutex/shared_timed_mutex.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <atomic>
#include <thread>
#include <chrono>

namespace hamon_shared_mutex_test
{

namespace shared_timed_mutex_test
{

void test_one_writer()
{
	// One simultaneous writer.
	std::atomic<int> atom(-1);
	hamon::shared_timed_mutex mut;
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
	hamon::shared_timed_mutex mut;
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
	hamon::shared_timed_mutex mut;
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
	hamon::shared_timed_mutex mut;
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
	hamon::shared_timed_mutex mut;

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

void test_try_lock_for_and_try_lock_shared_for()
{
	// Test try_lock_for() and try_lock_shared_for(). No timing assumptions.
	{
		hamon::shared_timed_mutex stm;

		{
			EXPECT_TRUE(stm.try_lock_for(hamon::chrono::milliseconds(25)));

			std::thread t([&stm]
			{
				EXPECT_FALSE(stm.try_lock_for(hamon::chrono::milliseconds(25)));
				EXPECT_FALSE(stm.try_lock_shared_for(hamon::chrono::milliseconds(25)));
			});

			t.join();
			stm.unlock();
		}

		{
			EXPECT_TRUE(stm.try_lock_shared_for(hamon::chrono::milliseconds(25)));

			std::thread t([&stm]
			{
				EXPECT_FALSE(stm.try_lock_for(hamon::chrono::milliseconds(25)));
				EXPECT_TRUE (stm.try_lock_shared_for(hamon::chrono::milliseconds(25)));
				stm.unlock_shared();
			});

			t.join();
			stm.unlock_shared();
		}
	}

	// Test delayed try_lock_for() success. GENEROUS timing assumptions.
	{
		std::atomic<int> atom(-5);
		hamon::shared_timed_mutex stm;
		hamon::vector<std::thread> threads;

		stm.lock_shared();

		for (int i = 0; i < 4; ++i)
		{
			threads.emplace_back([&atom, &stm]
			{
				++atom;
				while (atom < 0) {}
				EXPECT_TRUE(stm.try_lock_for(hamon::chrono::minutes(1)));
				const int val = (atom += 100);
				std::this_thread::sleep_for(std::chrono::milliseconds(25));
				EXPECT_TRUE(atom == val);
				stm.unlock();
			});
		}

		++atom;
		while (atom < 0) {}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		stm.unlock_shared();
		for (auto& t : threads)
		{
			t.join();
		}
		EXPECT_TRUE(atom == 400);
	}

	// Test delayed try_lock_shared_for() success. GENEROUS timing assumptions.
	{
		std::atomic<int> atom(-5);
		hamon::shared_timed_mutex stm;
		hamon::vector<std::thread> threads;

		stm.lock();

		for (int i = 0; i < 4; ++i)
		{
			threads.emplace_back([&atom, &stm]
			{
				++atom;
				while (atom < 0) {}
				EXPECT_TRUE(stm.try_lock_shared_for(hamon::chrono::minutes(1)));
				atom += 11;
				while (atom < 44) {}
				stm.unlock_shared();
			});
		}

		++atom;
		while (atom < 0) {}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		stm.unlock();
		for (auto& t : threads)
		{
			t.join();
		}
		EXPECT_TRUE(atom == 44);
	}

	// THE GRAND FINALE: If try_lock_for() gives up due to stubborn readers,
	// it needs to deliver notifications. No timing assumptions.
	{
		std::atomic<bool> launch_readers(false);
		hamon::shared_timed_mutex stm;
		hamon::vector<std::thread> threads;

		stm.lock_shared();

		threads.emplace_back([&launch_readers, &stm]
		{
			EXPECT_FALSE(stm.try_lock_for(hamon::chrono::milliseconds(100)));
			launch_readers = true;
		});

		threads.emplace_back([&launch_readers, &stm]
		{
			while (!launch_readers)
			{
				if (!stm.try_lock_shared())
				{
					launch_readers = true;
				}
				else
				{
					stm.unlock_shared();
				}
			}
		});

		while (!launch_readers) {}

		std::atomic<int> readers(0);

		for (int i = 0; i < 4; ++i)
		{
			threads.emplace_back([&stm, &readers]
			{
				stm.lock_shared();
				++readers;
				while (readers < 4) {}
				stm.unlock_shared();
			});
		}

		for (auto& t : threads)
		{
			t.join();
		}

		EXPECT_TRUE(readers == 4);
		stm.unlock_shared();
	}
}

GTEST_TEST(SharedMutexTest, SharedTimedMutexTest)
{
	test_one_writer();
	test_multiple_readers();
	test_writer_blocking_readers();
	test_readers_blocking_writer();
	test_try_lock_and_try_lock_shared();
	test_try_lock_for_and_try_lock_shared_for();
}

}	// namespace shared_timed_mutex_test

}	// namespace hamon_shared_mutex_test
