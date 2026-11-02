/**
 *	@file	unit_test_condition_variable_condition_variable_any_notify_all.cpp
 *
 *	@brief	notify_all のテスト
 *
 *	void notify_all() noexcept;
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/mutex.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_condition_variable_any_test
{

namespace notify_all_test
{

hamon::condition_variable_any cv;

typedef hamon::timed_mutex L0;
typedef hamon::unique_lock<L0> L1;

L0 m0;

const unsigned threadCount = 2;
bool pleaseExit = false;
hamon::atomic<unsigned> notReady;

void helper()
{
	L1 lk(m0);
	--notReady;
	while (pleaseExit == false)
	{
		cv.wait(lk);
	}
}

GTEST_TEST(ConditionVariableAnyTest, NotifyAllTest)
{
	static_assert(hamon::is_same_v<decltype(cv.notify_all()), void>, "");
	static_assert(noexcept(cv.notify_all()), "");

	notReady = threadCount;
	hamon::vector<hamon::thread> threads(threadCount);
	for (unsigned i = 0; i < threadCount; i++)
	{
		threads[i] = hamon::thread(helper);
	}

	{
		while (notReady > 0)
		{
			hamon::this_thread::yield();
		}
		// At this point, both threads have had a chance to acquire the lock and are
		// either waiting on the condition variable or about to wait.
		L1 lk(m0);
		pleaseExit = true;
		// POSIX does not guarantee reliable scheduling if notify_all is called
		// without the lock being held.
		cv.notify_all();
	}

	// The test will hang if not all of the threads were woken.
	for (unsigned i = 0; i < threadCount; i++)
	{
		threads[i].join();
	}
}

}	// namespace notify_all_test

}	// namespace hamon_condition_variable_any_test
