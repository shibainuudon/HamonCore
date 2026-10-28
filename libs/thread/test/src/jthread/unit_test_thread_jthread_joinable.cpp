/**
 *	@file	unit_test_thread_jthread_joinable.cpp
 *
 *	@brief	joinable のテスト
 *
 *	bool joinable() const noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/atomic.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace joinable_test
{

static_assert(noexcept(hamon::declval<hamon::jthread const&>().joinable()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread const&>().joinable()), bool>, "");

GTEST_TEST(JThreadTest, JoinableTest)
{
	// Default constructed
	{
		const hamon::jthread jt;
		bool result = jt.joinable();
		EXPECT_FALSE(result);
	}

	// Non-default constructed
	{
		const hamon::jthread jt([] {});
		bool result = jt.joinable();
		EXPECT_TRUE(result);
	}

	// Non-default constructed
	// the thread of execution has not finished
	{
		hamon::atomic_bool done{false};
		const hamon::jthread jt([&done] { done.wait(false); });
		bool result = jt.joinable();
		done = true;
		done.notify_all();
		EXPECT_TRUE(result);
	}
}

}	// namespace joinable_test

}	// namespace hamon_jthread_test
