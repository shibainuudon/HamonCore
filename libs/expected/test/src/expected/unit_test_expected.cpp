/**
 *	@file	unit_test_expected.cpp
 *
 *	@brief	expected のテスト
 */

#include <hamon/expected.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <cstdlib>

namespace hamon_expected_test
{

namespace expected_test
{

enum class parse_error
{
	invalid_input,
	overflow
};

auto parse_number(hamon::string_view str)
	-> hamon::expected<double, parse_error>
{
	const char* begin = str.data();
	char* end;
	double retval = std::strtod(begin, &end);

	if (begin == end)
	{
		return hamon::unexpected<parse_error>(parse_error::invalid_input);
	}
	else if (hamon::isinf(retval))
	{
		return hamon::unexpected<parse_error>(parse_error::overflow);
	}

	str.remove_prefix(static_cast<hamon::size_t>(end - begin));
	return retval;
}

GTEST_TEST(ExpectedTest, ExpectedTest)
{
	{
		auto const num = parse_number("42");
		EXPECT_TRUE(num.has_value());
		EXPECT_EQ(42, *num);
	}
	{
		auto const num = parse_number("43abc");
		EXPECT_TRUE(num.has_value());
		EXPECT_EQ(43, *num);
	}
	{
		auto const num = parse_number("meow");
		EXPECT_TRUE(!num.has_value());
		EXPECT_EQ(parse_error::invalid_input, num.error());
	}
	{
		auto const num = parse_number("inf");
		EXPECT_TRUE(!num.has_value());
		EXPECT_EQ(parse_error::overflow, num.error());
	}
}

}	// namespace expected_test

}	// namespace hamon_expected_test
