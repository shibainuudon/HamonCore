/**
 *	@file	unit_test_mutex_mutex_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_move_constructible_v<hamon::mutex>, "");
