/**
 *	@file	unit_test_format_basic_format_parse_context.cpp
 *
 *	@brief	basic_format_parse_context のテスト
 *
 *	template<class charT>
 *	class basic_format_parse_context;
 */

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/format_parse_context.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "noexcept_test.hpp"

namespace hamon_format_test
{

namespace basic_format_parse_context_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename CharT>
HAMON_CXX20_CONSTEXPR bool test(CharT const* fmt)
{
	static_assert(hamon::is_same_v<
		typename hamon::basic_format_parse_context<CharT>::char_type,
		CharT>);
	static_assert(hamon::is_same_v<
		typename hamon::basic_format_parse_context<CharT>::const_iterator,
		typename hamon::basic_string_view<CharT>::const_iterator>);
	static_assert(hamon::is_same_v<
		typename hamon::basic_format_parse_context<CharT>::iterator,
		typename hamon::basic_format_parse_context<CharT>::const_iterator>);

	{
		hamon::basic_format_parse_context<CharT> context(fmt);
		HAMON_ASSERT_NOEXCEPT_TRUE(context.begin());
		HAMON_ASSERT_NOEXCEPT_TRUE(context.end());
		VERIFY(hamon::to_address(context.begin()) == &fmt[0]);
//		VERIFY(hamon::to_address(context.end()) == &fmt[3]);

		context.advance_to(context.begin() + 1);
		VERIFY(hamon::to_address(context.begin()) == fmt + 1);
		context.advance_to(context.begin() + 1);
		VERIFY(hamon::to_address(context.begin()) == fmt + 2);
		context.advance_to(context.begin() + 1);
		VERIFY(context.begin() == context.end());
	}
	{
		hamon::basic_string_view view{ fmt };
		hamon::basic_format_parse_context context(view);
		HAMON_ASSERT_NOEXCEPT_TRUE(context.begin());
		HAMON_ASSERT_NOEXCEPT_TRUE(context.end());
		VERIFY(context.begin() == view.begin());
		VERIFY(context.end() == view.end());

		context.advance_to(context.begin() + 1);
		VERIFY(hamon::to_address(context.begin()) == fmt + 1);
		context.advance_to(context.begin() + 1);
		VERIFY(hamon::to_address(context.begin()) == fmt + 2);
		context.advance_to(context.begin() + 1);
		VERIFY(context.begin() == context.end());
	}
	return true;
}

namespace next_arg_id_test
{

constexpr bool test()
{
	hamon::format_parse_context context("", 10);
	for (hamon::size_t i = 0; i < 10; ++i)
	{
		VERIFY(i == context.next_arg_id());
	}

	return true;
}

void test_exception()
{
	{
		hamon::format_parse_context context("", 1);
		EXPECT_NO_THROW(context.next_arg_id());
	}
	{
		hamon::format_parse_context context("", 1);
		context.check_arg_id(0);
		EXPECT_THROW(context.next_arg_id(), hamon::format_error);
	}
}

}	// namespace next_arg_id_test

namespace check_arg_id_test
{

constexpr bool test()
{
	hamon::format_parse_context context("", 10);
	for (hamon::size_t i = 0; i < 10; ++i)
	{
		context.check_arg_id(i);
	}

	return true;
}

void test_exception()
{
	{
		hamon::format_parse_context context("", 1);
		EXPECT_NO_THROW(context.check_arg_id(0));
	}
	{
		hamon::format_parse_context context("", 1);
		context.next_arg_id();
		EXPECT_THROW(context.check_arg_id(0), hamon::format_error);
	}

	for (hamon::size_t i = 0; i < 10; ++i)
	{
		hamon::format_parse_context context("", i);
		EXPECT_NO_THROW(context.check_arg_id(0));
		EXPECT_NO_THROW(context.check_arg_id(i));	// Out of bounds access is valid if !std::is_constant_evaluated()
	}
}

}	// namespace check_arg_id_test

#undef VERIFY

GTEST_TEST(FormatTest, BasicFormatParseContextTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test("abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(L"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(u8"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(u"abc"));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(U"abc"));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(next_arg_id_test::test());
	next_arg_id_test::test_exception();

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(check_arg_id_test::test());
	check_arg_id_test::test_exception();
}

}	// namespace basic_format_parse_context_test

}	// namespace hamon_format_test
