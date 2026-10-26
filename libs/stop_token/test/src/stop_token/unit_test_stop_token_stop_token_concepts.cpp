/**
 *	@file	unit_test_stop_token_stop_token_concepts.cpp
 *
 *	@brief	コンセプトのテスト
 */

#include <hamon/stop_token/stop_token.hpp>
#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/stop_token/unstoppable_token.hpp>

// [stoptoken.general]/1
static_assert(hamon::stoppable_token<hamon::stop_token>, "");
static_assert(!hamon::unstoppable_token<hamon::stop_token>, "");
