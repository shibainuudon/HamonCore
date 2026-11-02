/**
 *	@file	unit_test_condition_variable_cv_status.cpp
 *
 *	@brief	cv_status のテスト
 *
 *	enum class cv_status { no_timeout, timeout };
 */

#include <hamon/condition_variable/cv_status.hpp>
#include <hamon/type_traits.hpp>

static_assert(hamon::is_scoped_enum_v<hamon::cv_status>, "");

static_assert(static_cast<int>(hamon::cv_status::no_timeout) == 0, "");
static_assert(static_cast<int>(hamon::cv_status::timeout)    == 1, "");
