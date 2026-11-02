/**
 *	@file	unit_test_condition_variable_condition_variable_any_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>

static_assert(!hamon::is_move_constructible_v<hamon::condition_variable_any>, "");
