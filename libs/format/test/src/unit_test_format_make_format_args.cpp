/**
 *	@file	unit_test_format_make_format_args.cpp
 *
 *	@brief	make_format_args のテスト
 *
 *	template<class Context = format_context, class... Args>
 *	format-arg-store<Context, Args...>
 *	make_format_args(Args&... fmt_args);
 */

#include <hamon/format/make_format_args.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/utility/forward.hpp>
#include <gtest/gtest.h>

namespace hamon_format_test
{

namespace make_format_args_test
{

template <class... Args>
concept can_make_format_args = requires(Args&&... args) { hamon::make_format_args(hamon::forward<Args>(args)...); };

static_assert( can_make_format_args<int&>, "");
static_assert(!can_make_format_args<int>, "");
static_assert(!can_make_format_args<int&&>, "");

GTEST_TEST(FormatTest, MakeFormatArgsTest)
{
	int i              = 1;
	char c             = 'c';
	hamon::nullptr_t p = nullptr;
	bool b             = false;
	auto store = hamon::make_format_args(i, p, b, c);

	static_assert(hamon::same_as<
		decltype(store),
		hamon::detail::format_arg_store<hamon::format_context, int, hamon::nullptr_t, bool, char>>, "");
}

}	// namespace make_format_args_test

}	// namespace hamon_format_test
