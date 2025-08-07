/**
 *	@file	format_test_map_exceptions.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_MAP_EXCEPTIONS_HPP
#define HAMON_FORMAT_TEST_MAP_EXCEPTIONS_HPP

#include <hamon/format/format_kind.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/deque.hpp>
#include <hamon/flat_map.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/map.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/unordered_map.hpp>
#include <hamon/utility/move.hpp>

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

namespace hamon_format_test
{

namespace map_exceptions_test
{

//
// Char
//

template <class CharT, class ExceptionTest>
void test_char(ExceptionTest check_exception)
{
	hamon::map<CharT, CharT> input{{CharT('a'), CharT('A')}, {CharT('c'), CharT('C')}, {CharT('b'), CharT('B')}};

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

	check_exception(SV("{:^^{}:#>11}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 44);
}

//
// char -> wchar_t
//

template <class ExceptionTest>
void test_char_to_wchar(ExceptionTest check_exception)
{
	hamon::map<char, char> input{{'a', 'A'}, {'c', 'C'}, {'b', 'B'}};

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

	//check_exception(SV("{::}<}"), input);
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

	check_exception(SV("{:^^{}:#>11}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 44);
}

//
// Bool
//
template <class CharT, class ExceptionTest>
void test_bool(ExceptionTest check_exception, auto&& input)
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

	check_exception(SV("{:^^{}:#>10}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 41);
}

template <class CharT, class ExceptionTest>
void test_bool(ExceptionTest check_exception)
{
	// duplicates are stored in order of insertion
	test_bool<CharT>(check_exception, hamon::multimap<bool, int>{{true, 42}, {false, 0}, {true, 1}});
	test_bool<CharT>(check_exception, hamon::flat_multimap<bool, int, hamon::less<bool>, hamon::deque<bool>>{{true, 42}, {false, 0}, {true, 1}});
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

	check_exception(SV("{:^^{}:#>10}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 41);
}

template <class CharT, class ExceptionTest>
void test_int(ExceptionTest check_exception)
{
	test_int<CharT>(check_exception, hamon::map<int, int>{{1, -1}, {42, -42}, {-42, 42}});
	test_int<CharT>(check_exception, hamon::flat_map<int, int>{{1, -1}, {42, -42}, {-42, 42}});
}

//
// Floating point
//

template <class CharT, class ExceptionTest>
void test_floating_point(ExceptionTest check_exception)
{
	hamon::map<double, double> input{{1.0, -1.0}, {-42, 42}};

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

	check_exception(SV("{:^^{}:#>10}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 29);
}

//
// Pointer
//

template <class CharT, class ExceptionTest>
void test_pointer(ExceptionTest check_exception)
{
	hamon::unordered_map<const void*, hamon::nullptr_t> input{{0, 0}};

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

	check_exception(SV("{:^^{}:#>11}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 18);
}

//
// String
//

template <class CharT, class ExceptionTest>
void test_string(ExceptionTest check_exception)
{
	hamon::map<hamon::basic_string<CharT>, hamon::basic_string<CharT>> input{
		{STR("hello"), STR("HELLO")}, {STR("world"), STR("WORLD")}};

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

	check_exception(SV("{:^^{}:#>21}"), input);
	check_exception(SV("{:^^{}:#>{}}"), input, 51);
}

//
// Handle
//

template <class CharT, class ExceptionTest>
void test_status(ExceptionTest check_exception)
{
	hamon::unordered_multimap<status, status> input{{status::foobar, status::foo}, {status::foobar, status::bar}};

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
	check_exception(SV("{:s}"), input);
	check_exception(SV("{:?s}"), input);

	// Underlying can't have a format-spec
}

//
// Adaptor
//

class adaptor
{
	using adaptee = hamon::map<int, int>;

public:
	using key_type = typename adaptee::key_type;
	using mapped_type = typename adaptee::mapped_type;
	using iterator = typename adaptee::iterator;

	iterator begin() { return data_.begin(); }
	iterator end() { return data_.end(); }

	explicit adaptor(hamon::map<int, int>&& data) : data_(hamon::move(data)) {}

private:
	adaptee data_;
};

static_assert(hamon::format_kind<adaptor> == hamon::range_format::map);

template <class CharT, class ExceptionTest>
void test_adaptor(ExceptionTest check_exception)
{
	test_int<CharT>(check_exception, adaptor{hamon::map<int, int>{{1, -1}, {42, -42}, {-42, 42}}});
}

}	// namespace map_exceptions_test

//
// Driver
//

template <class CharT, class ExceptionTest>
void test_map_exceptions(ExceptionTest check_exception)
{
	map_exceptions_test::test_char<CharT>(check_exception);
	if (hamon::same_as<CharT, wchar_t>) // avoid testing twice
	{
		map_exceptions_test::test_char_to_wchar(check_exception);
	}
	map_exceptions_test::test_bool<CharT>(check_exception);
	map_exceptions_test::test_int<CharT>(check_exception);
	map_exceptions_test::test_floating_point<CharT>(check_exception);
	map_exceptions_test::test_pointer<CharT>(check_exception);
	map_exceptions_test::test_string<CharT>(check_exception);
	map_exceptions_test::test_status<CharT>(check_exception);
	map_exceptions_test::test_adaptor<CharT>(check_exception);
}

}	// namespace hamon_format_test

#undef SV
#undef STR

#endif // HAMON_FORMAT_TEST_MAP_EXCEPTIONS_HPP
