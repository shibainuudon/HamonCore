/**
 *	@file	unit_test_stop_token.cpp
 *
 *	@brief	stop_token のテスト
 */

#include <hamon/stop_token.hpp>
#include <hamon/thread.hpp>
#include <gtest/gtest.h>

#if 0
namespace hamon_stop_token_test
{

void f(hamon::stop_token stop_token, int value)
{
	while (!stop_token.stop_requested())
	{
		std::cout << value++ << ' ' << std::flush;
		hamon::this_thread::sleep_for(hamon::chrono::milliseconds(200));
	}
	std::cout << std::endl;
}

GTEST_TEST(StopTokenTest, OverviewTest)
{
    hamon::jthread thread(f, 5); // prints 5 6 7 8... for approximately 3 seconds
    hamon::this_thread::sleep_for(hamon::chrono::seconds(3));
    // The destructor of jthread calls request_stop() and join().
}

}	// namespace hamon_stop_token_test
#endif
