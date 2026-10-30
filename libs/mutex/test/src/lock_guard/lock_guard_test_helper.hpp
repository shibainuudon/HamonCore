/**
 *	@file	lock_guard_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_LOCK_GUARD_TEST_HELPER_HPP
#define HAMON_LOCK_GUARD_TEST_HELPER_HPP

namespace hamon_lock_guard_test
{

struct MyMutex
{
	bool locked = false;

	MyMutex() = default;

	~MyMutex()
	{
		EXPECT_FALSE(locked);
	}

	void lock()
	{
		EXPECT_FALSE(locked);
		locked = true;
	}

	void unlock()
	{
		EXPECT_TRUE(locked);
		locked = false;
	}

	MyMutex(MyMutex const&) = delete;
	MyMutex& operator=(MyMutex const&) = delete;
};

}	// namespace hamon_lock_guard_test

#endif // HAMON_LOCK_GUARD_TEST_HELPER_HPP
