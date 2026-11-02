/**
 *	@file	unit_test_condition_variable_condition_variable_any_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	condition_variable_any& operator=(const condition_variable_any&) = delete;
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>

static_assert(!hamon::is_copy_assignable_v<hamon::condition_variable_any>, "");
