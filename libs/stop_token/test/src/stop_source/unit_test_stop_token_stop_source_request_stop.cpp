/**
 *	@file	unit_test_stop_token_stop_source_request_stop.cpp
 *
 *	@brief	request_stop のテスト
 *
 *	bool request_stop() noexcept;
 */

#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/stop_token/nostopstate_t.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_source_test
{

namespace request_stop_test
{

static_assert(noexcept(hamon::declval<hamon::stop_source&>().request_stop()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_source&>().request_stop()), bool>, "");

GTEST_TEST(StopSourceTest, StopRequestedTest)
{
	{
		hamon::stop_source ss1;
		hamon::stop_source ss2(hamon::nostopstate);

		EXPECT_TRUE(ss1.request_stop());

		// 二度目以降の停止要求は効果を持たない
		EXPECT_FALSE(ss1.request_stop());

		// 停止状態を所有していない stop_source に対しては
		// 停止要求を作成できない
		EXPECT_FALSE(ss2.request_stop());
	}

	// If *this does not have ownership of a stop state, returns false
	{
		hamon::stop_source ss{ hamon::nostopstate };

		static_assert(noexcept(ss.request_stop()), "");
		static_assert(hamon::is_same_v<decltype(ss.request_stop()), bool>, "");

		auto ret = ss.request_stop();
		EXPECT_FALSE(ret);
		EXPECT_FALSE(ss.stop_requested());
	}

	// Otherwise, atomically determines whether the owned stop state has received
	// a stop request, and if not, makes a stop request
	{
		hamon::stop_source ss;

		auto ret = ss.request_stop();
		EXPECT_TRUE(ret);
		EXPECT_TRUE(ss.stop_requested());
	}

	// already requested
	{
		hamon::stop_source ss;
		ss.request_stop();
		EXPECT_TRUE(ss.stop_requested());

		auto ret = ss.request_stop();
		EXPECT_FALSE(ret);
		EXPECT_TRUE(ss.stop_requested());
	}

	// If the request was made, the callbacks registered by
	// associated stop_callback objects are synchronously called.
	{
		hamon::stop_source ss;
		auto st = ss.get_token();

		bool cb1Called = false;
		bool cb2Called = false;
		auto f1 = [&] { cb1Called = true; };
		auto f2 = [&] { cb2Called = true; };
		hamon::stop_callback<decltype(f1)> sc1(st, f1);
		hamon::stop_callback<decltype(f2)> sc2(st, f2);

		ss.request_stop();
		EXPECT_TRUE(cb1Called);
		EXPECT_TRUE(cb2Called);
	}
}

}	// namespace request_stop_test

}	// namespace hamon_stop_token_test
