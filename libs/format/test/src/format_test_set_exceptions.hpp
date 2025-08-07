/**
 *	@file	format_test_set_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_SET_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_SET_EXCEPTIONS_HPP

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/pair.hpp>
#include <hamon/set.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/tuple.hpp>
#include <hamon/unordered_set.hpp>
#include <hamon/utility/move.hpp>
#include "format_test_helper.hpp"

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace set_exceptions_test
{

//
// Char
//

template <class CharT, class ExceptionTest>
void test_char_default(ExceptionTest check_exception)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	// ***** Only underlying has a format-spec

	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(false, SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec

	check_exception(SV("{:^^{}::>2}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 17);
}

// A set can be written as a string, based on
//   [tab:formatter.range.type]
//   s  T shall be charT. ...
// This does not seem very useful, but it is allowed.
template <class CharT, class ExceptionTest>
void test_char_string(ExceptionTest check_exception)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<s}"), input);
	check_exception(SV("{:{<s}"), input);

	// *** sign ***
	check_exception(SV("{:-s}"), input);
	check_exception(SV("{:+s}"), input);
	check_exception(SV("{: s}"), input);

	// *** alternate form ***
	check_exception(SV("{:#s}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0s}"), input);

	// *** precision ***
	check_exception(SV("{:.s}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:Ls}"), input);

	// *** n
	check_exception(SV("{:ns}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);
	check_exception(SV("{::<s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{:s:}"), input);

	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(false, SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:5s:5}"), input);
}

// A set can be written as a debug_string, based on
//   [tab:formatter.range.type]
//   ?s T shall be charT. ...
// This does not seem very useful, but it is allowed.
template <class CharT, class ExceptionTest>
void test_char_escaped_string(ExceptionTest check_exception)
{
	hamon::set input{ CharT('a'), CharT('c'), CharT('b') }; // input not sorted.

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<?s}"), input);
	check_exception(SV("{:{<?s}"), input);
	check_exception(SV("{::<?s}"), input);

	// *** sign ***
	check_exception(SV("{:-?s}"), input);
	check_exception(SV("{:+?s}"), input);
	check_exception(SV("{: ?s}"), input);

	// *** alternate form ***
	check_exception(SV("{:#?s}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0?s}"), input);

	// *** precision ***
	check_exception(SV("{:.?s}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L?s}"), input);

	// *** n
	check_exception(SV("{:n?s}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{:?s:}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:5?s:5}"), input);
}

template <class CharT, class ExceptionTest>
void test_char(ExceptionTest check_exception)
{
	test_char_default<CharT>(check_exception);
	test_char_string<CharT>(check_exception);
	test_char_escaped_string<CharT>(check_exception);
}

//
// char -> wchar_t
//

template <class ExceptionTest>
void test_char_to_wchar(ExceptionTest check_exception)
{
	hamon::set input{ 'a', 'c', 'b' }; // input not sorted.

	using CharT = wchar_t;

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(SV("{:m}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(false, SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec

	check_exception(SV("{:^^{}::>2}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 17);

	// The types s and ?s may only be used when using range_formatter<T, charT>
	// where the types T and charT are the same. This means this can't be used for
	// range_formatter<wchar_t, char> even when formatter<wchar_t, char> has a
	// debug-enabled specialization.

	using CharT = wchar_t;
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:?s}"), input);
}

//
// Bool
//

template <class CharT, class ExceptionTest>
void test_bool(ExceptionTest check_exception)
{
	hamon::set input{ true, false };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 23);
}

template <class CharT, class ExceptionTest>
void test_bool_multiset(ExceptionTest check_exception)
{
	hamon::multiset<bool, hamon::greater<bool>> input{ true, false, true }; // unordered

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 32);
}

//
// Integral
//

template <class CharT, class ExceptionTest>
void test_int(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(false, SV("{::b}"), input);
	check_exception(false, SV("{::B}"), input);
//	check_exception(false, SV("{::c}"), input);	// TODO
	check_exception(false, SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(false, SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(false, SV("{::x}"), input);
	check_exception(false, SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 33);
}

template <class CharT, class ExceptionTest>
void test_int(ExceptionTest check_exception)
{
	test_int<CharT>(check_exception, hamon::set{ 1, 42, 2, -42 });      // unsorted
	test_int<CharT>(check_exception, hamon::multiset{ 1, 42, 2, -42 }); // unsorted
}

//
// Floating point
//

template <class CharT, class ExceptionTest>
void test_floating_point(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** type ***
	check_exception(false, SV("{::a}"), input);
	check_exception(false, SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(false, SV("{::e}"), input);
	check_exception(false, SV("{::E}"), input);
	check_exception(false, SV("{::f}"), input);
	check_exception(false, SV("{::F}"), input);
	check_exception(false, SV("{::g}"), input);
	check_exception(false, SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5.2}"), input);
	check_exception(SV("{:^^{}::>{}.2}"), input, 33);
	check_exception(SV("{:^^{}::>{}.{}}"), input, 33, 5);
}

template <class CharT, class ExceptionTest>
void test_floating_point(ExceptionTest check_exception)
{
	test_floating_point<CharT>(check_exception, hamon::set{ -42.5f, 0.0f, 1.25f, 42.5f });
	test_floating_point<CharT>(check_exception, hamon::multiset{ -42.5, 0.0, 1.25, 42.5 });
	test_floating_point<CharT>(check_exception, hamon::set{ -42.5l, 0.0l, 1.25l, 42.5l });
}

//
// Pointer
//

template <class CharT, class ExceptionTest>
void test_pointer(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:#}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(false, SV("{::p}"), input);
	check_exception(false, SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>5}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 12);
}

template <class CharT, class ExceptionTest>
void test_pointer(ExceptionTest check_exception)
{
	// Note nullptr_t can only be equality compared so not used in a set.
	test_pointer<CharT>(check_exception, hamon::unordered_set{ static_cast<const void*>(0) });
	test_pointer<CharT>(check_exception, hamon::unordered_multiset{ static_cast<void*>(0) });
}

//
// String
//

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:#}"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(false, SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(false, SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(true,  SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}::>8}"), input);
	check_exception(SV("{:^^{}::>{}}"), input, 25);
}

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception)
{
	test_string<CharT>(check_exception, hamon::set{ STR("Hello"), STR("world") });
	test_string<CharT>(check_exception, hamon::set{ SV("Hello"), SV("world") });
}

//
// Handle
//

template <class CharT, class ExceptionTest>
void test_status(ExceptionTest check_exception)
{
	hamon::set input{ status::foo, status::bar, status::foobar }; // unordered input

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::*<7}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:X}"), input);
}

//
// Pair
//

template <class CharT, class ExceptionTest>
void test_pair_tuple(ExceptionTest check_exception, auto&& input)
{
	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(false, SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(false, SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 31);
}

template <class CharT, class ExceptionTest>
void test_pair_tuple(ExceptionTest check_exception)
{
	test_pair_tuple<CharT>(check_exception, hamon::set{ hamon::make_pair(1, CharT('a')), hamon::make_pair(42, CharT('*')) });
	test_pair_tuple<CharT>(check_exception, hamon::set{ hamon::make_tuple(1, CharT('a')), hamon::make_tuple(42, CharT('*')) });
}

//
// Tuple 1
//

template <class CharT, class ExceptionTest>
void test_tuple_int(ExceptionTest check_exception)
{
	hamon::set input{ hamon::make_tuple(42), hamon::make_tuple(99) };

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 23);
}

//
// Tuple 3
//

template <class CharT, class ExceptionTest>
void test_tuple_int_int_int(ExceptionTest check_exception)
{
	hamon::set input{ hamon::make_tuple(42, 99, 0), hamon::make_tuple(1, 10, 100) }; // unordered

	// ***** underlying has no format-spec

	// *** align-fill & width ***
	check_exception(SV("{:}<}"), input);
	check_exception(SV("{:{<}"), input);

	// *** sign ***
	check_exception(SV("{:-}"), input);
	check_exception(SV("{:+}"), input);
	check_exception(SV("{: }"), input);

	// *** alternate form ***
	check_exception(SV("{:#}"), input);

	// *** zero-padding ***
	check_exception(SV("{:0}"), input);

	// *** precision ***
	check_exception(SV("{:.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{:L}"), input);

	// *** type ***
	check_exception(true,  SV("{:a}"), input);
	check_exception(true,  SV("{:A}"), input);
	check_exception(true,  SV("{:b}"), input);
	check_exception(true,  SV("{:B}"), input);
	check_exception(true,  SV("{:c}"), input);
	check_exception(true,  SV("{:d}"), input);
	check_exception(true,  SV("{:e}"), input);
	check_exception(true,  SV("{:E}"), input);
	check_exception(true,  SV("{:f}"), input);
	check_exception(true,  SV("{:F}"), input);
	check_exception(true,  SV("{:g}"), input);
	check_exception(true,  SV("{:G}"), input);
	check_exception(true,  SV("{:o}"), input);
	check_exception(true,  SV("{:p}"), input);
	check_exception(true,  SV("{:P}"), input);
	check_exception(true,  SV("{:s}"), input);
	check_exception(true,  SV("{:x}"), input);
	check_exception(true,  SV("{:X}"), input);
	check_exception(true,  SV("{:?}"), input);
	check_exception(true,  SV("{:m}"), input);
	check_exception(false, SV("{:n}"), input);
	check_exception(true,  SV("{:?s}"), input);

	// ***** Only underlying has a format-spec
	check_exception(SV("{::}<}"), input);
	check_exception(SV("{::{<}"), input);

	// *** sign ***
	check_exception(SV("{::-}"), input);
	check_exception(SV("{::+}"), input);
	check_exception(SV("{:: }"), input);

	// *** alternate form ***
	check_exception(SV("{::#}"), input);

	// *** zero-padding ***
	check_exception(SV("{::05}"), input);

	// *** precision ***
	check_exception(SV("{::.}"), input);

	// *** locale-specific form ***
	check_exception(SV("{::L}"), input);

	// *** type ***
	check_exception(true,  SV("{::a}"), input);
	check_exception(true,  SV("{::A}"), input);
	check_exception(true,  SV("{::b}"), input);
	check_exception(true,  SV("{::B}"), input);
	check_exception(true,  SV("{::c}"), input);
	check_exception(true,  SV("{::d}"), input);
	check_exception(true,  SV("{::e}"), input);
	check_exception(true,  SV("{::E}"), input);
	check_exception(true,  SV("{::f}"), input);
	check_exception(true,  SV("{::F}"), input);
	check_exception(true,  SV("{::g}"), input);
	check_exception(true,  SV("{::G}"), input);
	check_exception(true,  SV("{::o}"), input);
	check_exception(true,  SV("{::p}"), input);
	check_exception(true,  SV("{::P}"), input);
	check_exception(true,  SV("{::s}"), input);
	check_exception(true,  SV("{::x}"), input);
	check_exception(true,  SV("{::X}"), input);
	check_exception(true,  SV("{::?}"), input);
	check_exception(true,  SV("{::m}"), input);
	check_exception(false, SV("{::n}"), input);
	check_exception(true,  SV("{::?s}"), input);

	// ***** Both have a format-spec
	check_exception(SV("{:^^{}:#>5}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 37);
}

//
// Adaptor
//

class adaptor
{
	using adaptee = hamon::set<int>;

public:
	using key_type = typename adaptee::key_type;
	using iterator = typename adaptee::iterator;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit adaptor(hamon::set<int>&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

static_assert(hamon::format_kind<adaptor> == hamon::range_format::set);

template <class CharT, class ExceptionTest>
void test_adaptor(ExceptionTest check_exception)
{
	test_int<CharT>(check_exception, adaptor{ hamon::set{1, 42, 2, -42} });
}

}	// namespace set_exceptions_test

//
// Driver
//

template <class CharT, class ExceptionTest>
void test_set_exceptions(ExceptionTest check_exception)
{
	set_exceptions_test::test_char<CharT>(check_exception);

	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		set_exceptions_test::test_char_to_wchar(check_exception);
	}

	set_exceptions_test::test_bool<CharT>(check_exception);
	set_exceptions_test::test_bool_multiset<CharT>(check_exception);
	set_exceptions_test::test_int<CharT>(check_exception);
	set_exceptions_test::test_floating_point<CharT>(check_exception);
	set_exceptions_test::test_pointer<CharT>(check_exception);
	set_exceptions_test::test_string<CharT>(check_exception);

	set_exceptions_test::test_status<CharT>(check_exception); // Has its own handler with its own parser

	set_exceptions_test::test_pair_tuple<CharT>(check_exception);
	set_exceptions_test::test_tuple_int<CharT>(check_exception);
	set_exceptions_test::test_tuple_int_int_int<CharT>(check_exception);

	set_exceptions_test::test_adaptor<CharT>(check_exception);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_SET_EXCEPTIONS_HPP
