/**
 *	@file	unit_test_format_format_string.cpp
 *
 *	@brief	format_string のテスト
 *
 *	template<class... Args>
 *	using format_string = basic_format_string<char, type_identity_t<Args>...>;
 */

#include <hamon/format/format_string.hpp>
#include <hamon/format/basic_format_string.hpp>
#include <hamon/concepts/same_as.hpp>

static_assert(hamon::same_as<hamon::format_string<>, hamon::basic_format_string<char>>);
static_assert(hamon::same_as<hamon::format_string<int>, hamon::basic_format_string<char, int>>);
static_assert(hamon::same_as<hamon::format_string<int, bool>, hamon::basic_format_string<char, int, bool>>);
static_assert(hamon::same_as<hamon::format_string<int, bool, void*>, hamon::basic_format_string<char, int, bool, void*>>);
