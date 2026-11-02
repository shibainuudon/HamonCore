/**
 *	@file	unit_test_condition_variable_condition_variable_any_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>

static_assert(!hamon::is_move_assignable_v<hamon::condition_variable_any>, "");
