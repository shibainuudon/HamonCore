/**
 *	@file	unit_test_stop_token_stop_callback_ctor_copy_move.cpp
 *
 *	@brief	コンストラクタのテスト
 *
 *	stop_callback(const stop_callback&) = delete;
 *	stop_callback(stop_callback&&) = delete;
 */

#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_callback_test
{

namespace ctor_copy_move_test
{

struct CallbackFunc
{
	void operator()() const {}
};

static_assert(!hamon::is_copy_constructible_v<hamon::stop_callback<CallbackFunc>>, "");
static_assert(!hamon::is_move_constructible_v<hamon::stop_callback<CallbackFunc>>, "");

}	// namespace ctor_copy_move_test

}	// namespace hamon_stop_callback_test
