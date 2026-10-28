/**
 *	@file	unit_test_thread_jthread_get_id.cpp
 *
 *	@brief	get_id のテスト
 *
 *	id get_id() const noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace get_id_test
{

static_assert(noexcept(hamon::declval<hamon::jthread const&>().get_id()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::jthread const&>().get_id()), hamon::jthread::id>, "");

GTEST_TEST(JThreadTest, GetIdTest)
{
	// Does not represent a thread
	{
		const hamon::jthread jt;
		hamon::jthread::id result = jt.get_id();
		EXPECT_TRUE(result == hamon::jthread::id());
	}

	// Represents a thread
	{
		const hamon::jthread jt([] {});
		hamon::jthread::id result = jt.get_id();
		EXPECT_TRUE(result != hamon::jthread::id());
	}
}

}	// namespace get_id_test

}	// namespace hamon_jthread_test
