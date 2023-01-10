/**
 *	@file	unit_test_debug_assert.cpp
 *
 *	@brief	HAMON_ASSERT のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <string>

#include <hamon/assert.hpp>

namespace hamon_debug_assert_test
{

inline int func(void) { return 1; }

GTEST_TEST(DebugAssertTest, SuccessTest)
{
	int x = 3;
	int y = 7;
	int z = 2;
	HAMON_ASSERT(x == 3);
	HAMON_ASSERT(3 == x);
	HAMON_ASSERT_MSG(x != y, "x equal y");
	HAMON_ASSERT(x < 4);
	HAMON_ASSERT(8 > y);
	HAMON_ASSERT_MSG(x <= 3, "x less than 3");
	HAMON_ASSERT(8 >= y);
	HAMON_ASSERT(x + y == 10);
	HAMON_ASSERT(x * 2 == 6);
	HAMON_ASSERT(x * y - z == 19);
	HAMON_ASSERT(x / func() == 3);

	HAMON_ASSERT(x == 3 && y == 7);
	HAMON_ASSERT(x > 0 && y < 8 && z == 2);

	HAMON_ASSERT(x == 3 || y == 7);
	HAMON_ASSERT(x == 2 || y == 7);
	HAMON_ASSERT(x == 3 || y == 6);
}

HAMON_CXX14_CONSTEXPR int add(int x, int y)
{
	return
		HAMON_ASSERT(x != 0),
		HAMON_ASSERT(y != 0),
		(x + y);
}

GTEST_TEST(DebugAssertTest, ConstexprTest)
{
#if defined(_MSC_VER) && _MSC_VER >= 1920 && _MSC_FULL_VER <= 192127702
	// Visual Studio Version 16.(0-1)だとconstexprにできない
	int x = add(2, 1);
#else
	HAMON_CXX14_CONSTEXPR int x = add(2, 1);
#endif
	HAMON_ASSERT(x == 3);
	HAMON_ASSERT_MSG(x == 3, "foo");

	int y = add(3, 1);
	HAMON_ASSERT(y == 4);
}

struct DebugAssertInfo
{
	int         invoke_count{};
	std::string file_name{};
	int         line_number{};
	std::string function_name{};
	std::string expr_str{};
	std::string evaluated_expr_str{};
	std::string msg{};
};

static DebugAssertInfo* s_info = nullptr;

static void MyAssertionHandler(const hamon::debug::assertion_info& info)
{
	s_info->invoke_count++;
	s_info->file_name          = info.file_name;
	s_info->line_number        = info.line_number;
	s_info->function_name      = info.function_name;
	s_info->expr_str           = info.expr_str;
	s_info->evaluated_expr_str = info.evaluated_expr_str;
	s_info->msg                = info.msg;
}

GTEST_TEST(DebugAssertTest, FailureTest)
{
	DebugAssertInfo info;
	s_info = &info;

	auto handler_old = hamon::debug::get_assertion_handler();
	hamon::debug::set_assertion_handler(MyAssertionHandler);

	int x = 3;
	int y = 7;
	int z = 2;
	int line_num = 0;

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x == 4);
	EXPECT_EQ(1, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x == 4", info.expr_str);
	EXPECT_EQ("(3 == 4)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT_MSG(5 == x, "hoge");
	EXPECT_EQ(2, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("5 == x", info.expr_str);
	EXPECT_EQ("(5 == 3)", info.evaluated_expr_str);
	EXPECT_EQ("hoge", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT_MSG(x != 3, "foo");
	EXPECT_EQ(3, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x != 3", info.expr_str);
	EXPECT_EQ("(3 != 3)", info.evaluated_expr_str);
	EXPECT_EQ("foo", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x < 2);
	EXPECT_EQ(4, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x < 2", info.expr_str);
	EXPECT_EQ("(3 < 2)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(6 > y);
	EXPECT_EQ(5, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("6 > y", info.expr_str);
	EXPECT_EQ("(6 > 7)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x <= 1);
	EXPECT_EQ(6, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x <= 1", info.expr_str);
	EXPECT_EQ("(3 <= 1)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(5 >= y);
	EXPECT_EQ(7, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("5 >= y", info.expr_str);
	EXPECT_EQ("(5 >= 7)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x + y == 11);
	EXPECT_EQ(8, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x + y == 11", info.expr_str);
	EXPECT_EQ("((3 + 7) == 11)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x * 2 != 6);
	EXPECT_EQ(9, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x * 2 != 6", info.expr_str);
	EXPECT_EQ("((3 * 2) != 6)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT_MSG(x * y + z == 24, "bar");
	EXPECT_EQ(10, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x * y + z == 24", info.expr_str);
	EXPECT_EQ("(((3 * 7) + 2) == 24)", info.evaluated_expr_str);
	EXPECT_EQ("bar", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x + func() != 4);
	EXPECT_EQ(11, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x + func() != 4", info.expr_str);
	EXPECT_EQ("((3 + 1) != 4)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	{
		int w = add(3, 0);
		(void)w;
		EXPECT_EQ(12, info.invoke_count);
		EXPECT_EQ(__FILE__, info.file_name);
		//EXPECT_EQ(line_num, info.line_number);
		//EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
		EXPECT_EQ("y != 0", info.expr_str);
		EXPECT_EQ("(0 != 0)", info.evaluated_expr_str);
		EXPECT_EQ("", info.msg);
	}

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x == 3 && y == 8);
	EXPECT_EQ(13, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x == 3 && y == 8", info.expr_str);
	EXPECT_EQ("((3 == 3) && 0)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x == 2 && y == 7);
	EXPECT_EQ(14, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x == 2 && y == 7", info.expr_str);
	EXPECT_EQ("((3 == 2) && 1)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	line_num = __LINE__ + 1;
	HAMON_ASSERT(x == 4 || y == 8);
	EXPECT_EQ(15, info.invoke_count);
	EXPECT_EQ(__FILE__, info.file_name);
	EXPECT_EQ(line_num, info.line_number);
	EXPECT_EQ(HAMON_CURRENT_FUNCTION, info.function_name);
	EXPECT_EQ("x == 4 || y == 8", info.expr_str);
	EXPECT_EQ("((3 == 4) || 0)", info.evaluated_expr_str);
	EXPECT_EQ("", info.msg);

	hamon::debug::set_assertion_handler(handler_old);
	s_info = nullptr;
}

}	// namespace hamon_debug_assert_test

#define HAMON_DISABLE_ASSERTS
#include <hamon/assert.hpp>

namespace hamon_debug_assert_test
{

GTEST_TEST(DebugAssertTest, DisableTest)
{
	DebugAssertInfo info;
	s_info = &info;

	auto handler_old = hamon::debug::get_assertion_handler();
	hamon::debug::set_assertion_handler(MyAssertionHandler);

	int x = 3;
	HAMON_ASSERT(x == 0);
	HAMON_ASSERT(x != 3);
	HAMON_ASSERT_MSG(x < 0, "");
	HAMON_ASSERT(x > 3);
	HAMON_ASSERT(x <= 2);
	HAMON_ASSERT(x >= 4);
	(void)x;

	EXPECT_EQ(0, info.invoke_count);

	hamon::debug::set_assertion_handler(handler_old);
	s_info = nullptr;
}

}	// namespace hamon_debug_assert_test

#undef HAMON_DISABLE_ASSERTS
#include <hamon/assert.hpp>

namespace hamon_debug_assert_test
{

GTEST_TEST(DebugAssertTest, EnableTest)
{
	DebugAssertInfo info;
	s_info = &info;

	auto handler_old = hamon::debug::get_assertion_handler();
	hamon::debug::set_assertion_handler(MyAssertionHandler);

	int x = 3;
	HAMON_ASSERT(x == 0);
	HAMON_ASSERT(x != 3);
	HAMON_ASSERT_MSG(x < 0, "");
	HAMON_ASSERT(x > 3);
	HAMON_ASSERT(x <= 2);
	HAMON_ASSERT(x >= 4);
	(void)x;

	EXPECT_EQ(6, info.invoke_count);

	hamon::debug::set_assertion_handler(handler_old);
	s_info = nullptr;
}

}	// namespace hamon_debug_assert_test
