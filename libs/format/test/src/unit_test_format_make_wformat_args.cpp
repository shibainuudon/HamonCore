/**
 *	@file	unit_test_format_make_wformat_args.cpp
 *
 *	@brief	make_wformat_args のテスト
 *
 *	template<class... Args>
 *	format-arg-store<wformat_context, Args...>
 *	make_wformat_args(Args&... args);
 */

#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/utility/forward.hpp>
#include <gtest/gtest.h>

namespace hamon_format_test
{

namespace make_wformat_args_test
{

template <class... Args>
concept can_make_wformat_args = requires(Args&&... args) { hamon::make_wformat_args(hamon::forward<Args>(args)...); };

static_assert( can_make_wformat_args<int&>, "");
static_assert(!can_make_wformat_args<int>, "");
static_assert(!can_make_wformat_args<int&&>, "");

GTEST_TEST(FormatTest, MakeWFormatArgsTest)
{
	int i              = 1;
	char c             = 'c';
	hamon::nullptr_t p = nullptr;
	bool b             = false;
	auto store = hamon::make_wformat_args(i, p, b, c);

	static_assert(hamon::same_as<
		decltype(store),
		hamon::detail::format_arg_store<hamon::wformat_context, int, hamon::nullptr_t, bool, char>>, "");
}

}	// namespace make_wformat_args_test

}	// namespace hamon_format_test
