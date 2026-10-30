/**
 *	@file	unit_test_mutex_timed_mutex_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/mutex/timed_mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_move_constructible_v<hamon::timed_mutex>, "");
