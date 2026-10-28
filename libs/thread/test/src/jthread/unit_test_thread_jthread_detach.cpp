/**
 *	@file	unit_test_thread_jthread_detach.cpp
 *
 *	@brief	detach のテスト
 *
 *	void detach();
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/thread/this_thread.hpp>
#include <hamon/atomic.hpp>
#include <hamon/chrono.hpp>
#include <hamon/optional.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace detach_test
{

static_assert(!noexcept(hamon::declval<hamon::jthread&>().detach()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread&>().detach()), void>, "");

GTEST_TEST(JThreadTest, DetachTest)
{
	// Effects: The thread represented by *this continues execution without the calling thread blocking.
	{
		hamon::atomic_bool start{ false };
		hamon::atomic_bool done{ false };
		hamon::optional<hamon::jthread> jt = hamon::jthread([&start, &done] {
			start.wait(false);
			done = true;
		});

		// If it blocks, it will deadlock here
		jt->detach();

		jt.reset();

		// The other thread continues execution
		start = true;
		start.notify_all();
		while (!done)
		{
		}
	}

	// Postconditions: get_id() == id().
	{
		hamon::jthread jt([] {});
		EXPECT_TRUE(jt.get_id() != hamon::jthread::id());
		jt.detach();
		EXPECT_TRUE(jt.get_id() == hamon::jthread::id());
	}

#if !defined(HAMON_NO_EXCEPTIONS)
	// Throws: system_error when an exception is required ([thread.req.exception]).
	// invalid_argument - if the thread is not joinable.
	{
		hamon::jthread jt;
		try
		{
			jt.detach();
			EXPECT_TRUE(false);
		}
		catch (const hamon::system_error& err)
		{
			EXPECT_TRUE(err.code() == hamon::errc::invalid_argument);
		}
	}
#endif

	hamon::this_thread::sleep_for(hamon::chrono::milliseconds{ 2 });
}

}	// namespace detach_test

}	// namespace hamon_jthread_test
