/**
 *	@file	unit_test_stop_token_stop_callback_ctad.cpp
 *
 *	@brief	テンプレート引数推論のテスト
 *
 *	template<class CallbackFn>
 *	stop_callback(stop_token, CallbackFn) -> stop_callback<CallbackFn>;
 */

#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/stop_token/stop_source.hpp>
#include <hamon/stop_token/stop_token.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/as_const.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>

namespace hamon_stop_callback_test
{

namespace ctad_test
{

GTEST_TEST(StopCallbackTest, CtadTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	int x = 0;

	hamon::stop_source ss;
	hamon::stop_token st = ss.get_token();
	auto f = [&]{ x += 10; };
	auto cb1 = hamon::stop_callback(st, f);
	auto cb2 = hamon::stop_callback(st, hamon::as_const(f));
	auto cb3 = hamon::stop_callback(st, hamon::move(f));
	auto cb4 = hamon::stop_callback(st, hamon::move(hamon::as_const(f)));
	static_assert(hamon::is_same_v<decltype(cb1), hamon::stop_callback<decltype(f)>>, "");
	static_assert(hamon::is_same_v<decltype(cb2), hamon::stop_callback<decltype(f)>>, "");
	static_assert(hamon::is_same_v<decltype(cb3), hamon::stop_callback<decltype(f)>>, "");
	static_assert(hamon::is_same_v<decltype(cb4), hamon::stop_callback<decltype(f)>>, "");

	ss.request_stop();
#endif
}

}	// namespace ctad_test

}	// namespace hamon_stop_callback_test
