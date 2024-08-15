/**
 *	@file	unit_test_memory_unique_ptr_ostream.cpp
 *
 *	@brief	operator<< のテスト
 *
 *	template<class E, class T, class Y, class D>
 *	basic_ostream<E, T>& operator<<(basic_ostream<E, T>& os, const unique_ptr<Y, D>& p);
 */

#include <hamon/memory/unique_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace unique_ptr_test
{

namespace ostream_test
{

GTEST_TEST(UniquePtrTest, OstreamTest)
{
	auto p = new int;
	hamon::unique_ptr<int> up(p);
	std::stringstream ss1;
	ss1 << up;
	std::stringstream ss2;
	ss2 << up;
	EXPECT_EQ(ss1.str(), ss2.str());
}

}	// namespace ostream_test

}	// namespace unique_ptr_test

}	// namespace hamon_memory_test
