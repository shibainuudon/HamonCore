/**
 *	@file	unit_test_stop_token_stop_token_stop_possible.cpp
 *
 *	@brief	stop_possible のテスト
 *
 *	bool stop_possible() const noexcept;
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/optional.hpp>
#include <hamon/thread.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_token_test
{

namespace stop_possible_test
{

static_assert(noexcept(hamon::declval<hamon::stop_token const&>().stop_possible()), "");
static_assert(hamon::is_same_v<decltype(hamon::declval<hamon::stop_token const&>().stop_possible()), bool>, "");

GTEST_TEST(StopTokenTest, StopPossibleTest)
{
	// no state
	{
		const hamon::stop_token st;
		EXPECT_FALSE(st.stop_possible());
	}

	// a stop request was not made and there are no associated stop_source objects
	{
		hamon::optional<hamon::stop_source> ss{ hamon::in_place };
		const auto st = ss->get_token();
		ss.reset();

		EXPECT_FALSE(st.stop_possible());
	}

	// a stop request was not made, but there is an associated stop_source objects
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		EXPECT_TRUE(st.stop_possible());
	}

	// a stop request was made and there are no associated stop_source objects
	{
		hamon::optional<hamon::stop_source> ss{ hamon::in_place };
		const auto st = ss->get_token();
		ss->request_stop();
		ss.reset();

		EXPECT_TRUE(st.stop_possible());
	}

	// a stop request was made and there is an associated stop_source objects
	{
		hamon::stop_source ss;
		const auto st = ss.get_token();
		ss.request_stop();
		EXPECT_TRUE(st.stop_possible());
	}

	// a stop request was made on a different thread and
	// there are no associated stop_source objects
	{
		hamon::optional<hamon::stop_source> ss{ hamon::in_place };
		const auto st = ss->get_token();

		hamon::thread t([&]() {
			ss->request_stop();
			ss.reset();
		});

		EXPECT_TRUE(st.stop_possible());
		t.join();
		EXPECT_TRUE(st.stop_possible());
	}
}

}	// namespace stop_possible_test

}	// namespace hamon_stop_token_test
