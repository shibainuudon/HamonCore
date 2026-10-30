/**
 *	@file	unit_test_mutex_mutex_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 */

#include <hamon/mutex/mutex.hpp>
#include <hamon/type_traits.hpp>

static_assert(!hamon::is_move_assignable_v<hamon::mutex>, "");
