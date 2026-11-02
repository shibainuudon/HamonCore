/**
 *	@file	unit_test_condition_variable_condition_variable_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	condition_variable(const condition_variable&) = delete;
 */

#include <hamon/condition_variable/condition_variable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>

static_assert(!hamon::is_copy_constructible_v<hamon::condition_variable>, "");
