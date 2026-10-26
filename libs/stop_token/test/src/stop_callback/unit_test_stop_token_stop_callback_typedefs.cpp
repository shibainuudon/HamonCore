/**
 *	@file	unit_test_stop_token_stop_callback_typedefs.cpp
 *
 *	@brief	デストラクタのテスト
 *
 *	using callback_type = CallbackFn;
 */

#include <hamon/stop_token/stop_callback.hpp>
#include <hamon/type_traits/is_same.hpp>

namespace hamon_stop_callback_test
{

namespace typedefs_test
{

struct Callback
{
	void operator()() const;
};

static_assert(hamon::is_same_v<hamon::stop_callback<Callback>::callback_type, Callback>, "");
static_assert(hamon::is_same_v<hamon::stop_callback<Callback const>::callback_type, Callback const>, "");
static_assert(hamon::is_same_v<hamon::stop_callback<Callback&>::callback_type, Callback&>, "");
static_assert(hamon::is_same_v<hamon::stop_callback<Callback const&>::callback_type, Callback const&>, "");
static_assert(hamon::is_same_v<hamon::stop_callback<Callback&&>::callback_type, Callback&&>, "");
static_assert(hamon::is_same_v<hamon::stop_callback<Callback const&&>::callback_type, Callback const&&>, "");

}	// namespace typedefs_test

}	// namespace hamon_stop_callback_test
