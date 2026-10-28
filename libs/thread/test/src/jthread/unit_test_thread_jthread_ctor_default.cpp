/**
 *	@file	unit_test_thread_jthread_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	jthread() noexcept;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_jthread_test
{

namespace ctor_default_test
{

static_assert( hamon::is_default_constructible_v<hamon::jthread>, "");
static_assert( hamon::is_nothrow_default_constructible_v<hamon::jthread>, "");
static_assert(!hamon::is_trivially_default_constructible_v<hamon::jthread>, "");
static_assert( hamon::is_implicitly_default_constructible_v<hamon::jthread>, "");

GTEST_TEST(JThreadTest, CtorDefaultTest)
{
	hamon::jthread jt;
	// [thread.jthread.cons]/2
	EXPECT_TRUE(jt.get_id() == hamon::thread::id());
	EXPECT_FALSE(jt.get_stop_source().stop_possible());
}

}	// namespace ctor_default_test

}	// namespace hamon_jthread_test
