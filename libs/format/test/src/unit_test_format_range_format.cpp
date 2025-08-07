/**
 *	@file	unit_test_format_range_format.cpp
 *
 *	@brief	range_format のテスト
 *
 *	enum class range_format {
 *		disabled,
 *		map,
 *		set,
 *		sequence,
 *		string,
 *		debug_string
 *	};
 */

#include <hamon/format/range_format.hpp>

static_assert(requires { hamon::range_format::disabled; });
static_assert(requires { hamon::range_format::map; });
static_assert(requires { hamon::range_format::set; });
static_assert(requires { hamon::range_format::sequence; });
static_assert(requires { hamon::range_format::string; });
static_assert(requires { hamon::range_format::debug_string; });
