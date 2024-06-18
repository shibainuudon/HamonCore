/**
 *	@file	unit_test_chrono_duration_from_stream.cpp
 *
 *	@brief	from_stream() のテスト
 *
 *	template<class charT, class traits, class Rep, class Period, class Alloc = allocator<charT>>
 *	basic_istream<charT, traits>&
 *	from_stream(basic_istream<charT, traits>& is, const charT* fmt,
 *		duration<Rep, Period>& d,
 *		basic_string<charT, traits, Alloc>* abbrev = nullptr,
 *		minutes* offset = nullptr);
 */

#include <hamon/chrono/duration.hpp>
#include <gtest/gtest.h>

namespace hamon_chrono_test
{

namespace duration_from_stream_test
{

GTEST_TEST(DurationTest, FromStreamTest)
{
	// TODO
}

}	// namespace duration_from_stream_test

}	// namespace hamon_chrono_test
