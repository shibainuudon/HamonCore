/**
 *	@file	unit_test_format_wformat_args.cpp
 *
 *	@brief	wformat_args のテスト
 *
 *	using wformat_args = basic_format_args<wformat_context>;
 */

#include <hamon/format/wformat_args.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::is_same_v<hamon::wformat_args, hamon::basic_format_args<hamon::wformat_context>>);
