/**
 *	@file	unit_test_system_error_is_error_code_enum.cpp
 *
 *	@brief	is_error_code_enum のテスト
 */

#include <hamon/system_error/is_error_code_enum.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/system_error/error_category.hpp>
#include <hamon/ios/io_errc.hpp>
#include <future>

static_assert(!hamon::is_error_code_enum<int>::value, "");
static_assert( hamon::is_error_code_enum<hamon::io_errc>::value, "");
static_assert( hamon::is_error_code_enum<std::future_errc>::value, "");
static_assert(!hamon::is_error_code_enum<hamon::errc>::value, "");
static_assert(!hamon::is_error_code_enum<hamon::error_category>::value, "");

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

static_assert(!hamon::is_error_code_enum_v<int>, "");
static_assert( hamon::is_error_code_enum_v<hamon::io_errc>, "");
static_assert( hamon::is_error_code_enum_v<std::future_errc>, "");
static_assert(!hamon::is_error_code_enum_v<hamon::errc>, "");
static_assert(!hamon::is_error_code_enum_v<hamon::error_category>, "");

#endif
