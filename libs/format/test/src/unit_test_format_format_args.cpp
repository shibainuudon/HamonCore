/**
 *	@file	unit_test_format_format_args.cpp
 *
 *	@brief	format_args のテスト
 *
 *	using format_args = basic_format_args<format_context>;
 */

#include <hamon/format/format_args.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::is_same_v<hamon::format_args, hamon::basic_format_args<hamon::format_context>>);
