/**
 *	@file	unit_test_system_error_system_error.cpp
 *
 *	@brief	system_error のテスト
 */

#include <hamon/system_error/system_error.hpp>
#include <hamon/system_error/errc.hpp>
#include <hamon/system_error/make_error_code.hpp>
#include <hamon/system_error/generic_category.hpp>
#include <hamon/system_error/system_category.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(SystemErrorTest, SystemErrorTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::permission_denied), "test"), hamon::system_error);
	EXPECT_THROW(hamon::detail::throw_system_error(hamon::make_error_code(hamon::errc::resource_deadlock_would_occur)), hamon::system_error);
	EXPECT_THROW(hamon::detail::throw_system_error(int(hamon::errc::operation_not_permitted), hamon::generic_category(), "test"), hamon::system_error);
	EXPECT_THROW(hamon::detail::throw_system_error(int(hamon::errc::operation_not_permitted), hamon::system_category()), hamon::system_error);
#endif
}
