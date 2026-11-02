/**
 *	@file	unit_test_condition_variable_condition_variable_any_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	condition_variable_any(const condition_variable_any&) = delete;
 */

#include <hamon/condition_variable/condition_variable_any.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>

static_assert(!hamon::is_copy_constructible_v<hamon::condition_variable_any>, "");
