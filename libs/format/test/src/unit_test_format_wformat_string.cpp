/**
 *	@file	unit_test_format_wformat_string.cpp
 *
 *	@brief	wformat_string のテスト
 *
 *	template<class... Args>
 *	using wformat_string = basic_format_string<wchar_t, type_identity_t<Args>...>;
 */

#include <hamon/format/wformat_string.hpp>
#include <hamon/format/basic_format_string.hpp>
#include <hamon/concepts/same_as.hpp>

static_assert(hamon::same_as<hamon::wformat_string<>, hamon::basic_format_string<wchar_t>>);
static_assert(hamon::same_as<hamon::wformat_string<int>, hamon::basic_format_string<wchar_t, int>>);
static_assert(hamon::same_as<hamon::wformat_string<int, bool>, hamon::basic_format_string<wchar_t, int, bool>>);
static_assert(hamon::same_as<hamon::wformat_string<int, bool, void*>, hamon::basic_format_string<wchar_t, int, bool, void*>>);
