/**
 *	@file	unit_test_memory_shared_ptr_ostream.cpp
 *
 *	@brief	operator<< のテスト
 *
 *	template<class E, class T, class Y>
 *	basic_ostream<E, T>& operator<<(basic_ostream<E, T>& os, const shared_ptr<Y>& p);
 */

#include <hamon/memory/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_memory_test
{

namespace shared_ptr_test
{

namespace ostream_test
{

GTEST_TEST(SharedPtrTest, OstreamTest)
{
	auto p = new int;
	hamon::shared_ptr<int> sp(p);
	std::stringstream ss1;
	ss1 << sp;
	std::stringstream ss2;
	ss2 << p;
	EXPECT_TRUE(ss1.str() == ss2.str());
}

}	// namespace ostream_test

}	// namespace shared_ptr_test

}	// namespace hamon_memory_test
