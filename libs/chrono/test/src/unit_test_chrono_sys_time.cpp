/**
 *	@file	unit_test_chrono_sys_time.cpp
 *
 *	@brief	sys_time のテスト
 */

#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

GTEST_TEST(ChronoTest, SysTimeTest)
{
#if 0	// TODO
	namespace chrono = hamon::chrono;
	chrono::sys_time<chrono::seconds> now = chrono::floor<chrono::seconds>(chrono::system_clock::now());
	std::cout << now << std::endl;
#endif
}

}	// namespace hamon_chrono_test
